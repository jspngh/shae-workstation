(function() {
"use strict";

/* Controls how the selected area looks and what a user has to do to select
 * an area. It will pass on the selected area to the QMMapView.
 * Abstract class.
 * @constructor
 * @param {google.maps.Map} map The map
 */
function MapSelection(map, formatting) {
    this.map = map;
    this.selectedArea = null;
    this.isSelecting = false;
    this.shiftPressed = false;
    this.formatting = formatting;
};

MapSelection.prototype = {

    /* Called automatically when the mouse is clicked on a given point on the map.
     * @param {google.maps.LatLng} point The point where it is clicked.
     */
    onMouseClicked: function(point) {
        throw "Error: method <onMouseClicked> not implemented by subclass.";
    },

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

    /* Called automatically when shift is pressed. */
    onShiftPressed: function() {
        throw "Error: method <onShiftPressed> not implemented by subclass.";
    },

    /* Called automatically when the shift key is released. */
    onShiftReleased: function() {
        throw "Error: method <onShiftReleased> not implemented by subclass.";
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
     * @return {Object} An object literal, containing the identifying
     *                  properties of the area.
     */
    getSelectedArea: function() {
        throw "Error: method <getSelectedArea> not implemented by subclass.";
    }
};

window.MapSelection = MapSelection;
})();

