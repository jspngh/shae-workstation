(function() {
    "use strict";

    /* Represents a marker on the map.
     * If the location is not set, the center of the map will be used.
     *
     * @param {google.maps.Map} map The map on which the marker should be shown.
     * @param {number} [locationLat] The latitude of the marker's location.
     * @param {number} [locationLng] The longitude of the marker's location.
     */
    function Marker(map, locationLat, locationLng) {
        this.map = map;
        this.canvas = document.createElement("canvas");
        this.imageData = null;

        var location;
        if(locationLat && locationLng)
            location = new google.maps.LatLng(locationLat, locationLng);
        else
            location = map.getCenter();

        this.marker = new google.maps.Marker({
            position: location,
        });
    }

    /* Move the marker to the given position.
     */
    Marker.prototype.show = function() {
        this.marker.setMap(this.map);
    };

    /* Move the marker to the given position.
     * @param {number} latitude The latitude of the marker's new location.
     * @param {number} longitude The longitude of the marker's new location.
     */
    Marker.prototype.moveTo = function(latitude, longitude) {
        this.marker.setPosition(new google.maps.LatLng(latitude, longitude));
    };

    /* Rotate the marker by a given amount of degrees.
     * @param {number} degrees The amount of rotated degrees. A positive value
     *                         will lead to a clockwise rotation.
     */
    Marker.prototype.rotate = function(degrees) {
        var self = this;
        if(!this.imageData) return;

        var img = document.createElement("img");
        img.src = this.imageData;
        img.onload = function() {
            self.canvas.width = img.width;
            self.canvas.height = img.height;

            var context = self.canvas.getContext("2d");
            context.translate(self.canvas.width/2, self.canvas.height/2);
            context.rotate(degrees * Math.PI / 180);
            context.drawImage(img, -(img.width)/2, -(img.height)/2);

            self.setIcon(self.canvas.toDataURL("image/png"));
        };
    };

    /* Set the marker's icon
     * @param {string} image The data-uri representing the image.
     * @param {object} [size] The preferredsize of the icon (should contain
     *                        both a width and height-property).
     */
    Marker.prototype.setIcon = function(image, size) {
        this.imageData = image.url;
        this.marker.setIcon(image);
    };

    /* Remove the marker from the map.
     */
    Marker.prototype.removeFromMap = function() {
        this.marker.setMap(null);
    };

    window.Marker = Marker;
})();

