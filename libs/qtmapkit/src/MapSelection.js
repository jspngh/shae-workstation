(function() {
    "use strict";

    /* Controls how the selected area looks and what a user has to do to select
     * an area. It will pass on the selected area to the QMMapView.
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

    /* Returns whether selection mode is enabled by the user.
     * @returns {boolean} Whether the keys to enable selection mode have
     *                    been pressed.
     */
    MapSelection.prototype.keysPressed = function() {
        return this.shiftPressed && this.mouseDown;
    };

    /* Creates a selection area on the map. If there was one before, it
     * is removed.
     * @param {google.maps.LatLngBounds} bounds The bounds of the selection area.
     */
    MapSelection.prototype.createSelectedArea = function(bounds) {
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

    /* Expands the selected area with a given coordinate
     * @param {google.maps.LatLng} latLng The coordinate
     */
    MapSelection.prototype.extendSelectedArea = function(latLng) {
        var bounds = this.selectedArea.getBounds();
        bounds.extend(latLng);
        this.selectedArea.setBounds(bounds);
        qMapView.jsSelectedAreaChanged(
            bounds.getNorthEast().lat(), bounds.getSouthWest().lng(),
            bounds.getSouthWest().lat(), bounds.getNorthEast().lng()
        );
    };

    /* Removes the selected area
     */
    MapSelection.prototype.removeSelectedArea = function() {
        this.selectedArea.setMap(null);
        this.selectedArea = null;
        qMapView.jsSelectedAreaDeleted();
    };

    /* Returns the selected area
     * @return {object} An object literal, containing north, south, east &
     * west properties.
     */
    MapSelection.prototype.getSelectedArea = function() {
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

    window.MapSelection = MapSelection;
})();

