(function() {
"use strict";

/* Allows the selection of a square. Extends MapSelection
 * @constructor
 * @param {google.maps.Map} map The map
 */
function SquareMapSelection(map) {
    MapSelection.call(this, map);

    this.keysPressed = function() {
        return this.shiftPressed && this.mouseDown;
    };

    this.onMouseMoved = function(point) {
        if(this.keysPressed() && this.isSelecting) {
            this.extendSelectedArea(point);
        }
    };

    this.onMouseDown = function(point) {
        this.mouseDown = true;
        if(this.keysPressed()) {
            this.map.setOptions({draggable: false});
            var bounds = new google.maps.LatLngBounds();
            bounds.extend(point);
            this.createSelectedArea(bounds);
            this.isSelecting = true;
        }
    };

    this.onMouseUp = function(point) {
        this.mouseDown = false;
        this.isSelecting = false;
        this.map.setOptions({draggable: true});
    };

    this.createSelectedArea = function(bounds) {
        if(this.selectedArea != null) this.removeSelectedArea();

        this.selectedArea = new google.maps.Rectangle({
            map: this.map,
            clickable: false,
            strokeColor: "#FF0000",
            strokeOpacity: 0.8,
            fillColor: "#FF0000",
            fillOpacity: 0.25,
            bounds: bounds
        });

        qMapView.jsSelectedAreaCreated(
            bounds.getNorthEast().lat(), bounds.getSouthWest().lng(),
            bounds.getSouthWest().lat(), bounds.getNorthEast().lng()
        );
    };

    this.extendSelectedArea = function(latLng) {
        var bounds = this.selectedArea.getBounds();
        bounds.extend(latLng);
        this.selectedArea.setBounds(bounds);
        qMapView.jsSelectedAreaChanged(
            bounds.getNorthEast().lat(), bounds.getSouthWest().lng(),
            bounds.getSouthWest().lat(), bounds.getNorthEast().lng()
        );
    };

    this.removeSelectedArea = function() {
        this.selectedArea.setMap(null);
        this.selectedArea = null;
        qMapView.jsSelectedAreaDeleted();
    };

    this.getSelectedArea = function() {
        if(this.selectedArea == null) return null;

        var northEast = this.selectedArea.getBounds().getNorthEast();
        var southWest = this.selectedArea.getBounds().getSouthWest();
        return {
            north: northEast.lat(),
            east: northEast.lng(),
            south: southWest.lat(),
            west: southWest.lng()
        };
    }
};

SquareMapSelection.prototype = Object.create(MapSelection.prototype, {
});
SquareMapSelection.prototype.constructor = SquareMapSelection;

window.SquareMapSelection = SquareMapSelection;
})();

