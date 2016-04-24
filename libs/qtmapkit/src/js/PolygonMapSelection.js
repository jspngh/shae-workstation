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
    this.paths = [];
    this.selectedArea = new google.maps.Polygon({
        map: this.map,
        clickable: false,
        strokeColor: "#FF0000",
        strokeOpacity: 0.8,
        fillColor: "#FF0000",
        fillOpacity: 0.25,
        paths: this.paths
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
        this.paths.push(latLng);
        this.selectedArea.setPaths(this.paths);
    };

    this.removeSelectedArea = function() {
        this.paths = [];
        this.selectedArea.setPaths(this.paths);
    };

    this.getSelectedArea = function() {
        return this.paths;
    };
};

PolygonMapSelection.prototype = Object.create(MapSelection.prototype, {
});
PolygonMapSelection.prototype.constructor = PolygonMapSelection;

window.PolygonMapSelection = PolygonMapSelection;
})();

