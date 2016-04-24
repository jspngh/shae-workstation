(function() {
"use strict";

/* Controls how the selected area looks and what a user has to do to select
 * an area. It will pass on the selected area to the QMMapView.
 * Abstract class.
 * @constructor
 * @param {google.maps.Map} map The map
 */
function MapSelection(map) {
    this.map = map;
    this.selectedArea = null;
    this.shiftPressed = false;
    this.mouseDown = false;
    this.isSelecting = false;
};

MapSelection.prototype = {

    /* Called automatically when the mouse moves to a given point on the map.
     * @param {google.maps.LatLng} point
     */
    onMouseMoved: function(point) {
        throw "Error: method <onMouseMoved> not implemented by subclass.";
    },

    /* Called automatically when the mouse is held down at a given point on the map.
     * @param {google.maps.LatLng} point
     */
    onMouseDown: function(point) {
        throw "Error: method <onMouseDown> not implemented by subclass.";
    },

    /* Called automatically when the mouse button went up at a given point on the map.
     * @param {google.maps.LatLng} point
     */
    onMouseUp: function(point) {
        throw "Error: method <onMouseUp> not implemented by subclass.";
    },

    /* Returns whether selection mode is enabled by the user.
     * @returns {boolean} Whether the keys to enable selection mode have
     *                    been pressed.
     */
    keysPressed: function() {
        throw "Error: method <keysPressed> not implemented by subclass.";
    },

    /* Creates a selection area on the map. If there was one before, it
     * is removed.
     * @param {google.maps.LatLngBounds} bounds The bounds of the selection area.
     */
    createSelectedArea: function(bounds) {
        throw "Error: method <createSelectedArea> not implemented by subclass.";
    },

    /* Expands the selected area with a given coordinate
     * @param {google.maps.LatLng} latLng The coordinate
     */
    extendSelectedArea: function(latLng) {
        throw "Error: method <extendSelectedArea> not implemented by subclass.";
    },

    /* Removes the selected area
     */
    removeSelectedArea: function() {
        throw "Error: method <removeSelectedArea> not implemented by subclass.";
    },

    /* Returns the selected area
     * @return {object} An object literal, containing north, south, east &
     * west properties.
     */
    getSelectedArea: function() {
        throw "Error: method <getSelectedArea> not implemented by subclass.";
    }
};

window.MapSelection = MapSelection;
})();

