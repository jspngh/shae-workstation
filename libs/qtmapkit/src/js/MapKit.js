(function() {
    "use strict";

    /* Contains all tools for a map, including a way to select areas.
     * @constructor
     * @param {number} lng The longitude at which the map will be centered.
     * @param {number} lat The latitude at which the map will be centered.
     * @param {string} type The map type (e.g. "SATELLITE", "ROADMAP", ...)
     * @param {number} zoom The zoom level of the map.
     */
    function MapKit(lng, lat, type, zoom) {
        this.map = this.initializeMap(lng, lat, type, zoom);
        this.geocoder = new google.maps.Geocoder();
        this.mapSelection = null;
        this.markers = {};

        this.addEventListeners();
    };

    /* Initialize google maps
     * @param {double} lng    The longitude of the map center
     * @param {double} lat    The latitude of the map center
     * @param {string} type   The type of map (one of "HYBRID", "ROADMAP", "SATELLITE", "TERRAIN")
     * @param {int}    zoom   The level of zooming (sane values are something in [0..20])
     */
    MapKit.prototype.initializeMap = function(lng, lat, type, zoom) {
        var mapOptions = {
            center: new google.maps.LatLng(lat, lng),
            mapTypeId: type,
            zoom: zoom,
            streetViewControl: false
        };
        return new google.maps.Map(document.getElementById("map_canvas"), mapOptions);
    };

    MapKit.prototype.addEventListeners = function() {
        var self = this;
        google.maps.event.addListener(self.map, "bounds_changed", function() {
            var bounds = self.map.getBounds();
            var ne = bounds.getNorthEast();
            var sw = bounds.getSouthWest();
            qMapView.jsRegionChangedTo(ne.lat(), sw.lat(), ne.lng(), sw.lng());
        });
        google.maps.event.addListener(self.map, "center_changed", function() {
            var center = self.map.getCenter();
            qMapView.jsCenterChangedTo(center.lat(), center.lng());
        });
        google.maps.event.addListener(self.map, "click", function(e) {
            var p = e.latLng;
            if(self.mapSelection) self.mapSelection.onMouseClicked(p);
            qMapView.jsMouseClickedAt(p.lat(), p.lng());
        });
        google.maps.event.addListener(self.map, "dblclick", function(e) {
            var p = e.latLng;
            qMapView.jsMouseDoubleClickedAt(p.lat(), p.lng());
        });
        google.maps.event.addListener(self.map, "rightclick", function(e) {
            var p = e.latLng;
            qMapView.jsMouseRightClickedAt(p.lat(), p.lng());
        });
        google.maps.event.addListener(self.map, "drag", function() {
            qMapView.mouseDragged();
        });
        google.maps.event.addListener(self.map, "dragstart", function() {
            qMapView.mouseDragStarted();
        });
        google.maps.event.addListener(self.map, "dragend", function() {
            qMapView.mouseDragEnded();
        });
        google.maps.event.addListener(self.map, "heading_changed", function() {
            qMapView.headingChanged();
        });
        google.maps.event.addListener(self.map, "idle", function() {
            qMapView.mapBecameIdle();
        });
        google.maps.event.addListener(self.map, "maptypeid_changed", function() {
            qMapView.jsMapTypeChangedTo(self.map.getMapTypeId());
        });
        google.maps.event.addListener(self.map, "mousemove", function(e) {
            var p = e.latLng;
            qMapView.jsMouseMovedTo(p.lat(), p.lng());
            if(self.mapSelection) self.mapSelection.onMouseMoved(p);
        });
        google.maps.event.addListener(self.map, "mousedown", function(e) {
            if(self.mapSelection) self.mapSelection.onMouseDown(e.latLng);
        });
        google.maps.event.addListener(self.map, "mouseup", function(e) {
            if(self.mapSelection) self.mapSelection.onMouseUp(e.latLng);
        });
        google.maps.event.addListener(self.map, "mouseover", function(e) {
            var p = e.latLng;
            qMapView.jsMouseEnteredAt(p.lat(), p.lng());
        });
        google.maps.event.addListener(self.map, "mouseout", function(e) {
            var p = e.latLng;
            qMapView.jsMouseLeftAt(p.lat(), p.lng());
        });
        google.maps.event.addListener(self.map, "tilesloaded", function() {
            qMapView.tilesLoaded();
        });
        google.maps.event.addListener(self.map, "tilt_changed", function() {
            qMapView.tilesChanged();
        });
        google.maps.event.addListener(self.map, "zoom_changed", function() {
            qMapView.zoomLevelChanged(self.map.getZoom());
        });
    }

    /* Returns the center of the map. */
    MapKit.prototype.getCenter = function() {
        var center = this.map.getCenter();
        return {
            latitude: center.lat(),
            longitude: center.lng()
        }
    };

    /* Sets the center of the map to the given coordinates.
     * @param {number} lat The latitude of the new center.
     * @param {number} lng The longitude of the new center.
     * @param {boolean} animated Whether this should be animated.
     */
    MapKit.prototype.setCenter = function(lat, lng, animated) {
        var latlng = new google.maps.LatLng(lat, lng);
        if (animated)
            this.map.panTo(latlng);
        else
            this.map.setCenter(latlng);
    };

    /* Sets the center of the map to a given location.
     * @param {string} address The location of the new center.
     * @param {number} animated Whether this should be animated.
     */
    MapKit.prototype.setCenterByAddress = function(address, animated) {
        var self = this;
        self.geocode(address, function(geometry) {
            if (animated)
                self.map.panToBounds(geometry.bounds);
            self.map.fitBounds(geometry.bounds);
        });
    };

    /* Returns the bounds of the map. */
    MapKit.prototype.getBounds = function() {
        var bounds = this.map.getBounds();
        var ne = bounds.getNorthEast();
        var sw = bounds.getSouthWest();
        return {
            "north": ne.lng(),
            "south": sw.lng(),
            "east": ne.lat(),
            "west": sw.lat()
        };
    };

    MapKit.prototype.panToBounds = function(north, south, east, west) {
        this.map.panToBounds(
          this.boundsFromCoordinates(north, south, east, west)
        );
    };

    MapKit.prototype.fitBounds = function(north, south, east, west) {
        this.map.fitBounds(
          this.boundsFromCoordinates(north, south, east, west)
        );
    };

    // Helper method
    MapKit.prototype.boundsFromCoordinates = function(north, south, east, west) {
        var ne = new google.maps.LatLng(north, east);
        var sw = new google.maps.LatLng(south, west);
        return new google.maps.LatLngBounds(sw, ne);
    };

    /* Translates an address into a pair of coordinates.
     * @param {string} address The address you want to translate.
     * @param {callback} successCallback The function that will be called on success.
     * @returns {LatLng} The coordinates of the best match, or null if none were found.
     */
    MapKit.prototype.geocode = function(address, successCallback) {
        this.geocoder.geocode( {"address": address}, function(results, status) {
            if(status == google.maps.GeocoderStatus.OK) {
                var bestGuess = results[0];
                successCallback(bestGuess.geometry);
            } else {
                return null;
            }
        });
    };

    /* --------- */
    /* SELECTION */
    /* --------- */
    MapKit.prototype.setSelectable = function(selectionType) {
        if(this.mapSelection) {
            this.mapSelection.removeSelectedArea();
            this.mapSelection = null;
        }

        switch(selectionType) {
            case "polygon":
                this.mapSelection = new PolygonMapSelection(this.map);
                break;
            case "square":
                this.mapSelection = new SquareMapSelection(this.map);
            default:
                this.mapSelection = null;
        }
    };

    MapKit.prototype.selectAreaOnMap = function(topLeftLat, topLeftLong, bottomRightLat, bottomRightLong) {
        if(!this.mapSelection) return;

        this.mapSelection.createSelectedArea(
            new google.maps.LatLngBounds(
                { lat: topLeftLat, lng: topLeftLong },
                { lat: bottomRightLat, lng: bottomRightLong }
            )
        );
    };

    MapKit.prototype.shiftKeyDown = function() {
        if(!this.mapSelection) return;

        this.mapSelection.onShiftPressed();
    };

    MapKit.prototype.shiftKeyUp = function() {
        if(!this.mapSelection) return;

        this.mapSelection.onShiftReleased();
    };

    /* --------- */
    /*  MARKERS  */
    /* --------- */
    MapKit.prototype.addMarker = function(id, locationLat, locationLng) {
        this.markers[id] = new Marker(this.map, locationLat, locationLng);
    }

    MapKit.prototype.getMarker = function(id) {
        return this.markers[id];
    }

    MapKit.prototype.removeMarker = function(id) {
        this.getMarker(id).removeFromMap();
        delete this.markers[id];
    }

    window.MapKit = MapKit;
})();

