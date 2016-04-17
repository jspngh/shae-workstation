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

        // Location stuff
        var location;
        if(locationLat && locationLng)
            location = new google.maps.LatLng(locationLat, locationLng);
        else
            location = map.getCenter();

        // Icon stuff
        this.canvas = document.createElement("canvas");
        this.image;
        this.imgLoadedPromise;
        this.rotation = 0;

        // Tracking stuff
        this.visitedPoints = [location];
        this.trackedPath = new google.maps.Polyline({
            map: this.map,
            path: this.visitedPoints,
            visible: false
        });

        // Actual marker
        this.marker = new google.maps.Marker({
            position: location,
            clickable: false
        });
    }

    /* Show the marker on the map.
     */
    Marker.prototype.show = function() {
        this.marker.setMap(this.map);
    };

    /* Track the marker's path.
     */
    Marker.prototype.trackPath = function() {
        this.trackedPath.setVisible(true);
    };

    /* Move the marker to the given position.
     * @param {number} latitude The latitude of the marker's new location.
     * @param {number} longitude The longitude of the marker's new location.
     */
    Marker.prototype.moveTo = function(latitude, longitude) {
        var point = new google.maps.LatLng(latitude, longitude);
        this.marker.setPosition(point);

        this.visitedPoints.push(point);
        this.trackedPath.setPath(this.visitedPoints);
    };

    /* Rotate the marker by a given amount of degrees.
     * @param {number} degrees The amount of rotated degrees. A positive value
     *                         will lead to a clockwise rotation.
     */
    Marker.prototype.rotate = function(degrees) {
        if(!this.image) return;

        var self = this;
        this.addTransformation(function(context) {
            context.rotate(degrees * Math.PI / 180);
            self.rotation += degrees * Math.PI / 180;
        });
    };

    Marker.prototype.scale = function(width, height) {
        if(!this.image) return;

        var self = this;
        this.addTransformation(function(context, image) {
            context.canvas.width *= width;
            context.canvas.height *= height;

            // Changing a canvas' width/height resets all transformations
            context.translate(context.canvas.width/2, context.canvas.height/2);
            context.rotate(self.rotation);
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
            // set canvas big enough so it doesn't crop the image after rotation.
            self.canvas.width = self.image.width * 2;
            self.canvas.height = self.image.height * 2;

            self.imgLoadedPromise.resolve();
        });
        this.image.src = uri;

        this.addTransformation(function(context, image) {
            context.translate(context.canvas.width/2, context.canvas.height/2);
        });
    };

    /*
     * Add a transformation before drawing the image.
     * Private method
     * @param {function} transformCallback The callback which will perform the
     *                                     transformation.
     */
    Marker.prototype.addTransformation = function(transformCallback) {
        var self = this;
        var context = self.canvas.getContext("2d");

        self.imgLoadedPromise.done(function() {
            // Clear previous
            context.clearRect(-self.image.width/2, -self.image.height/2,
                               self.image.width,  self.image.height);

            // Transform, then draw current
            transformCallback(context, self.image);
            context.drawImage(self.image, -self.image.width/2, -self.image.height/2);

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

