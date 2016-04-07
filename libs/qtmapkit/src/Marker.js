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
        this.imgLoadedPromise;

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
        this.marker.setPosition(
            new google.maps.LatLng(latitude, longitude)
        );
    };

    /* Rotate the marker by a given amount of degrees.
     * @param {number} degrees The amount of rotated degrees. A positive value
     *                         will lead to a clockwise rotation.
     */
    Marker.prototype.rotate = function(degrees) {
        if(!this.image) return;

        var self = this;
        this.addTransformation(function(context) {
            context.translate(context.canvas.width/2, context.canvas.height/2);
            context.rotate(degrees * Math.PI / 180);
            context.translate(-(context.canvas.width)/2, -(context.canvas.height)/2);
        });
    };

    Marker.prototype.scale = function(width, height) {
        if(!this.image) return;

        var self = this;
        this.addTransformation(function(context, image) {
            self.canvas.width *= width;
            self.canvas.height *= height;
            context.scale(width, height);
        });
    };

    /* Set the marker's icon
     * @param {string} image The data-uri representing the image.
     */
    Marker.prototype.setIcon = function(uri) {
        var self = this;
        this.image = new Image();
        this.imgLoadedPromise = $.Deferred();

        this.image.addEventListener("load", function() {
            self.imgLoadedPromise.resolve();
        });
        this.image.src = uri;

        this.addTransformation(function(context, image) {
            self.canvas.width = image.width;
            self.canvas.height = image.height;
            context.drawImage(image, 0, 0);
        });
    };

    Marker.prototype.addTransformation = function(drawingCallback) {
        var self = this;
        self.imgLoadedPromise = self.imgLoadedPromise.done(function() {
            var context = self.canvas.getContext("2d");
            // Clear previous
            context.save();
            context.setTransform(1, 0, 0, 1, 0, 0);
            context.clearRect(0, 0, self.canvas.width, self.canvas.height);
            context.restore();

            drawingCallback(context, self.image);
            context.drawImage(self.image, 0, 0);

            self.marker.setIcon({
                url: self.canvas.toDataURL("image/png"),
                anchor: new google.maps.Point(
                            Math.floor(self.canvas.width/2),
                            Math.floor(self.canvas.height/2)
                        )
            });
        });
    };

    /* Remove the marker from the map.
     */
    Marker.prototype.removeFromMap = function() {
        this.marker.setMap(null);
    };

    window.Marker = Marker;
})();

