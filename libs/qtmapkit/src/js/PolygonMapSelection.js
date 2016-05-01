(function() {
"use strict";

/* Allows the selection of a polygon. Extends MapSelection
 * @constructor
 * @param {google.maps.Map} map The map
 */
function PolygonMapSelection(map) {
    MapSelection.call(this, map);

    /* --------- */
    /* VARIABLES */
    /* --------- */
    this.corners = [];
    this.selectedArea = new google.maps.Polygon({
        map: this.map,
        clickable: false,
        strokeColor: "#FF0000",
        strokeOpacity: 0.8,
        fillColor: "#FF0000",
        fillOpacity: 0.25,
        paths: this.corners
    });

    /* --------- */
    /*  METHODS  */
    /* --------- */
    this.onMouseClicked = function(point) {
        if(!this.shiftPressed) return;

        this.extendSelectedArea(point);
    };

    this.onShiftPressed = function() {
        this.removeSelectedArea();
        this.map.setOptions({draggable: false});
        this.shiftPressed = true;
    };

    this.onShiftReleased = function() {
        this.map.setOptions({draggable: true});
        this.shiftPressed = false;
    };

    // These mouse events are not used.
    this.onMouseMoved = function(point) {};
    this.onMouseDown = function(point) {};
    this.onMouseUp = function(point) {};

    this.createSelectedArea = function(bounds) {
    };

    this.extendSelectedArea = function(latLng) {
        this.corners.push(latLng);
        this.selectedArea.setPaths(this.corners);
    };

    this.removeSelectedArea = function() {
        this.corners = [];
        this.selectedArea.setPaths(this.corners);
    };

    this.getSelectedArea = function() {
        // QVariants can only retrieve fields, not process methods.
        var result = [];
        this.corners.foreach(function(latLng) {
            result.push(latLng.toJSON());
        });
        return result;
    };
};

PolygonMapSelection.prototype = Object.create(MapSelection.prototype, {
});
PolygonMapSelection.prototype.constructor = PolygonMapSelection;

window.PolygonMapSelection = PolygonMapSelection;
})();

