(function() {
    // Fuck crappy JS constructs
    "use strict";

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

    // Expose only the init-function. Afterwards, a MapKit object will be exposed.
    window.initialize = initialize;
})();

