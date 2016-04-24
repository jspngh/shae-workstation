(function() {
"use strict";

/* Allows the selection of a polygon. Extends MapSelection
 * @constructor
 * @param {google.maps.Map} map The map
 */
function PolygonMapSelection(map) {
    MapSelection.call(this, map);

    this.keysPressed = function() {
    };

    this.onMouseMoved = function(point) {
    };

    this.onMouseDown = function(point) {
    };

    this.onMouseUp = function(point) {
    };

    this.createSelectedArea = function(bounds) {
    };

    this.extendSelectedArea = function(latLng) {
    };

    this.removeSelectedArea = function() {
    };

    this.getSelectedArea = function() {
    }
};

PolygonMapSelection.prototype = Object.create(MapSelection.prototype, {
});
PolygonMapSelection.prototype.constructor = PolygonMapSelection;

window.PolygonMapSelection = PolygonMapSelection;
})();

