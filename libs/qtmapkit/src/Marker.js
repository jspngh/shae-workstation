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
        this.image;
        this.drawCallbacks = [];

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
        if(!this.imageData) return;

        var self = this;
        this.drawCallbacks.push(function(context, image) {
            context.clearRect(0, 0, context.canvas.width, context.canvas.height);
            context.translate(context.canvas.width/2, context.canvas.height/2);
            context.rotate(degrees * Math.PI / 180);
            context.drawImage(image, -(image.width)/2, -(image.height)/2);
        });
        this.setMarkerIcon();
    };

    Marker.prototype.scale = function(width, height) {
        if(!this.imageData) return;

        var self = this;
        this.drawCallbacks.push(function(context, image) {
            context.clearRect(0, 0, context.canvas.width, context.canvas.height);
            context.translate(context.canvas.width/2, context.canvas.height/2);
            context.scale(width, height);
            context.drawImage(image, -(image.width)/2, -(image.height)/2);
        });
        this.setMarkerIcon();
    };

    /* Set the marker's icon
     * @param {string} image The data-uri representing the image.
     */
    Marker.prototype.setIcon = function(image) {
        var self = this;
        this.imageData = image;
        this.drawCallbacks.push(function(context, image) {
            context.drawImage(image, 0, 0);
        });
        this.setMarkerIcon(true);
    };

    // Private helper method
    Marker.prototype.setMarkerIcon = function(init) {
        var self = this;
        var img = this.image || new Image();
        img.addEventListener("load", function() {
            if(init) {
                self.canvas.width = img.width;
                self.canvas.height = img.height;
            }

            var context = self.canvas.getContext("2d");
            context.save();
            self.drawCallbacks.shift()(context, img);
            context.restore();
            self.marker.setIcon(self.canvas.toDataURL("image/png"));
        }, true);
        img.src = this.imageData;
    };

    /* Remove the marker from the map.
     */
    Marker.prototype.removeFromMap = function() {
        this.marker.setMap(null);
    };

    window.Marker = Marker;
})();

