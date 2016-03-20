(function() {

    /*
     * @constructor
     */
    function MapKit(lng, lat, type, zoom) {
        this.map = null;
        initializeMap(lng, lat, type, zoom);
        this.geocoder = new google.maps.Geocoder();
        this.selectionMode = new SelectionMode(this.map);

        /* Initialize google maps
         * @param {double} lng    The longitude of the map center
         * @param {double} lat    The latitude of the map center
         * @param {string} type   The type of map (one of "HYBRID", "ROADMAP", "SATELLITE", "TERRAIN")
         * @param {int}    zoom   The level of zooming (sane values are something in [0..20])
         */
        this.initializeMap = function(lng, lat, type, zoom) {
            var mapOptions = {
                "center": new google.maps.LatLng(lat, lng),
                "mapTypeId": type,
                "zoom": zoom,
                "streetViewControl": false
            };
            this.map = new google.maps.Map(document.getElementById("map_canvas"), mapOptions);
            google.maps.event.addListener(map, "bounds_changed", function() {
                var bounds = map.getBounds();
                var ne = bounds.getNorthEast();
                var sw = bounds.getSouthWest();
                qMapView.jsRegionChangedTo(ne.lat(), sw.lat(), ne.lng(), sw.lng());
            });
            google.maps.event.addListener(map, "center_changed", function() {
                var center = map.getCenter();
                qMapView.jsCenterChangedTo(center.lat(), center.lng());
            });
            google.maps.event.addListener(map, "click", function(e) {
                var p = e.latLng;
                qMapView.jsMouseClickedAt(p.lat(), p.lng());
            });
            google.maps.event.addListener(map, "dblclick", function(e) {
                var p = e.latLng;
                qMapView.jsMouseDoubleClickedAt(p.lat(), p.lng());
            });
            google.maps.event.addListener(map, "rightclick", function(e) {
                var p = e.latLng;
                qMapView.jsMouseRightClickedAt(p.lat(), p.lng());
            });
            google.maps.event.addListener(map, "drag", function() {
                qMapView.mouseDragged();
            });
            google.maps.event.addListener(map, "dragstart", function() {
                qMapView.mouseDragStarted();
            });
            google.maps.event.addListener(map, "dragend", function() {
                qMapView.mouseDragEnded();
            });
            google.maps.event.addListener(map, "heading_changed", function() {
                qMapView.headingChanged();
            });
            google.maps.event.addListener(map, "idle", function() {
                qMapView.mapBecameIdle();
            });
            google.maps.event.addListener(map, "maptypeid_changed", function() {
                qMapView.jsMapTypeChangedTo(map.getMapTypeId());
            });
            google.maps.event.addListener(map, "mousemove", function(e) {
                var p = e.latLng;
                qMapView.jsMouseMovedTo(p.lat(), p.lng());

                if(selectionMode.keysPressed() && selectionMode.isSelecting) {
                    bounds.extend(e.latLng);
                    selectionMode.editSelectedArea(bounds);
                }
            });
            google.maps.event.addListener(map, "mousedown", function(e) {
                selectionMode.mouseDown = true;
                if(selectionMode.keysPressed()) {
                    map.setOptions({draggable: false});
                    bounds = new google.maps.LatLngBounds();
                    bounds.extend(e.latLng);
                    selectionMode.createSelectedArea(bounds);
                    selectionMode.isSelecting = true;
                }
            });
            google.maps.event.addListener(map, "mouseup", function(e) {
                selectionMode.mouseDown = false;
                selectionMode.isSelecting = false;
                map.setOptions({draggable: true});
            });
            google.maps.event.addListener(map, "mouseover", function(e) {
                var p = e.latLng;
                qMapView.jsMouseEnteredAt(p.lat(), p.lng());
            });
            google.maps.event.addListener(map, "mouseout", function(e) {
                var p = e.latLng;
                qMapView.jsMouseLeftAt(p.lat(), p.lng());
            });
            google.maps.event.addListener(map, "tilesloaded", function() {
                qMapView.tilesLoaded();
            });
            google.maps.event.addListener(map, "tilt_changed", function() {
                qMapView.tilesChanged();
            });
            google.maps.event.addListener(map, "zoom_changed", function() {
                qMapView.zoomLevelChanged(map.getZoom());
            });
        };

        /* Returns the center of the map. */
        this.getCenter = function() {
            var center = this.map.getCenter();
            return {
                "latitude": center.lat(),
                "longitude": center.lng()
            }
        };

        /* Sets the center of the map to the given coordinates.
         * @param {number} lat The latitude of the new center.
         * @param {number} lng The longitude of the new center.
         * @param {number} animated Whether this should be animated.
         */
        this.setCenter = function(lat, lng, animated) {
            var latlng = new google.maps.LatLng(lat, lng);
            if (animated)
                map.panTo(latlng);
            else
                map.setCenter(latlng);
        };

        /* Sets the center of the map to a given location.
         * @param {string} address The location of the new center.
         * @param {number} animated Whether this should be animated.
         */
        this.setCenterByAddress = function(address, animated) {
            geocode(address, function(geometry) {
                if (animated)
                    map.panToBounds(geometry.bounds);
                map.fitBounds(geometry.bounds);
            });
        };

        /* Returns the bounds of the map. */
        this.getBounds = function() {
            var bounds = map.getBounds();
            var ne = bounds.getNorthEast();
            var sw = bounds.getSouthWest();
            return {
                "north": ne.lng(),
                "south": sw.lng(),
                "east": ne.lat(),
                "west": sw.lat()
            };
        };

        this.panToBounds = function(north, south, east, west) {
            map.panToBounds(boundsFromCoordinates(north, south, east, west));
        };

        this.fitBounds = function(north, south, east, west) {
            this.map.fitBounds(boundsFromCoordinates(north, south, east, west));
        };

        // Helper method
        this.boundsFromCoordinates = function(north, south, east, west) {
            var ne = new google.maps.LatLng(north, east);
            var sw = new google.maps.LatLng(south, west);
            return new google.maps.LatLngBounds(sw, ne);
        };

        /* Translates an address into a pair of coordinates.
         * @param {string} address The address you want to translate.
         * @param {callback} successCallback The function that will be called on success.
         * @returns {LatLng} The coordinates of the best match, or null if none were found.
         */
        this.geocode = function(address, successCallback) {
            this.geocoder.geocode( {"address": address}, function(results, status) {
                if(status == google.maps.GeocoderStatus.OK) {
                    var bestGuess = results[0];
                    successCallback(bestGuess.geometry);
                } else {
                    return null;
                }
            });
        };

        this.selectAreaOnMap = function(topLeftLat, topLeftLong, bottomRightLat, bottomRightLong) {
            this.selectionMode.createSelectedArea(
                new google.maps.LatLngBounds(
                    { lat: topLeftLat, lng: topLeftLong },
                    { lat: bottomRightLat, lng: bottomRightLong }
                )
            );
        };

        this.shiftKeyDown = function() {
            selectionMode.shiftPressed = true;
        };

        this.shiftKeyUp = function() {
            selectionMode.shiftPressed = false;
        };
    };

    /* Controls how the selected area looks and what a user has to do to select
     * an area. It will pass on the selected area to the QMMapView.
     * @constructor
     * @param {google.maps.Map} map The map
     */
    function SelectionMode(map) {
        this.selectedArea = null;
        this.shiftPressed = false;
        this.mouseDown = false;
        this.isSelecting = false;

        this.keysPressed = function() {
            return this.shiftPressed && this.mouseDown;
        };
        this.createSelectedArea = function(bounds) {
            if(this.selectedArea != null) this.removeSelectedArea();

            this.selectedArea = new google.maps.Rectangle({
                map: map,
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
        this.editSelectedArea = function(bounds) {
            selectionMode.selectedArea.setBounds(bounds);
            qMapView.jsSelectedAreaChanged(
                bounds.getNorthEast().lat(), bounds.getSouthWest().lng(),
                bounds.getSouthWest().lat(), bounds.getNorthEast().lng()
            );
        };
        this.removeSelectedArea = function() {
            this.selectedArea.setMap(null);
            this.selectedArea = null;
            qMapView.jsSelectedAreaDeleted();
        };
    };

    /* Represents a list of a specific type of markers.
     * @constructor
     * @param {google.maps.Map} map The map
     * @param {google.maps.Icon} icon The icon that should be used for the markers in this list
     */
    function MarkerList(map, icon) {
        this.map = map;
        this.markers = {};
        this.icon = icon;

        this.get = function(id) {
            return this.markers[id];
        };
        this.add = function(id, latitude, longitude) {
            var marker = new google.maps.Marker({
                map: map,
                title: id,
                position: new google.maps.LatLng(latitude, longitude)
            });
            this.markers[id] = marker;
        };
        this.remove = function(id) {
            var marker = this.get(id);
            if(marker) {
                marker.map = null;
                delete this.markers[id];
            }
        };
    }

    /*
     * @returns {boolean} Whether the initialization succeeded.
     */
    function initialize(lng, lat, type, zoom) {
        // Check if scripts failed to load first (due to e.g. connection errors)
        if(typeof google !== 'object') {
            return false;
        }

        window.mapKit = new MapKit(lng, lat, type, zoom);

        return true;
    }

    // Exports
    window.initialize = initialize;
})();

