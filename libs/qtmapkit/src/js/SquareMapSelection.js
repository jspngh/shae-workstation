(function() {
"use strict";

/* Allows the selection of a square. Extends MapSelection
 * @constructor
 * @param {google.maps.Map} map The map
 */
function SquareMapSelection(map, formatting) {
    MapSelection.call(this, map, formatting);

    /* --------- */
    /* VARIABLES */
    /* --------- */
    this.mouseDown = false;

    /* --------- */
    /*  METHODS  */
    /* --------- */

    /* Returns whether selection mode is enabled by the user.
     * @returns {boolean} Whether the keys to enable selection mode have
     *                    been pressed.
     */
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

    this.onShiftPressed = function() {
        this.shiftPressed = true;
    };

    this.onShiftReleased = function() {
        this.shiftPressed = false;
    };

    // Unused
    this.onMouseClicked = function(point) {};

    this.createSelectedArea = function(bounds) {
        if(this.selectedArea != null) this.removeSelectedArea();

        this.selectedArea = new google.maps.Rectangle({
            map: this.map,
            clickable: false,
            strokeColor: this.formatting.strokeColor,
            strokeOpacity: this.formatting.strokeOpacity,
            fillColor: this.formatting.fillColor,
            fillOpacity: this.formatting.fillOpacity,
            bounds: bounds
        });

        qMapView.selectedAreaCreated();
    };

    this.extendSelectedArea = function(latLng) {
        var bounds = this.selectedArea.getBounds();
        bounds.extend(latLng);
        this.selectedArea.setBounds(bounds);
        qMapView.jsSelectedAreaChanged();
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
    };
};

SquareMapSelection.prototype = Object.create(MapSelection.prototype, {
});
SquareMapSelection.prototype.constructor = SquareMapSelection;

window.SquareMapSelection = SquareMapSelection;
})();

