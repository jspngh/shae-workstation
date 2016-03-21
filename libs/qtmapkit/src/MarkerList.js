(function() {
    "use strict";

    /* Represents a list of a specific type of markers.
     * @constructor
     * @param {google.maps.Map} map The map
     * @param {google.maps.Icon} icon The icon that should be used for the markers in this list
     */
    function MarkerList(map, icon) {
        this.map = map;
        this.markers = {};
        this.icon = icon;
    }

    MarkerList.prototype.get = function(id) {
        return this.markers[id];
    };

    MarkerList.prototype.add = function(id, latitude, longitude) {
        var marker = new google.maps.Marker({
            map: this.map,
            position: new google.maps.LatLng(latitude, longitude)
        });
        this.markers[id] = marker;
    };

    MarkerList.prototype.remove = function(id) {
        var marker = this.get(id);
        if(marker) {
            marker.map = null;
            delete this.markers[id];
        }
    };

    window.MarkerList = MarkerList;
})();

