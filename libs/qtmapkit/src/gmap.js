var map = null;
var markers = {};
var markerIndex = 0;
var shiftIsPressed = false;
var mouseDown = false;
var selectedArea = null;
var selectedBounds = null;

function initialize(lng, lat, type, zoom)
{
    var mapOptions = {
        "center": new google.maps.LatLng(lat, lng),
        "mapTypeId": type,
        "zoom": zoom,
        "streetViewControl": false
    };
    map = new google.maps.Map(document.getElementById("map_canvas"),
                              mapOptions);
    google.maps.event.addListener(map, "bounds_changed", function() {
        var bounds = map.getBounds();
        var ne = bounds.getNorthEast();
        var sw = bounds.getSouthWest();
        qMapView.regionDidChangeTo(ne.lat(), sw.lat(), ne.lng(), sw.lng());
    });
    google.maps.event.addListener(map, "center_changed", function() {
        var center = map.getCenter();
        qMapView.centerDidChangeTo(center.lat(), center.lng());
    });
    google.maps.event.addListener(map, "click", function(e) {
        var p = e.latLng;
        qMapView.mouseDidClickAt(p.lat(), p.lng());
    });
    google.maps.event.addListener(map, "dblclick", function(e) {
        var p = e.latLng;
        qMapView.mouseDidDoubleClickAt(p.lat(), p.lng());
    });
    google.maps.event.addListener(map, "rightclick", function(e) {
        var p = e.latLng;
        qMapView.mouseDidRightClickAt(p.lat(), p.lng());
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
        qMapView.mapTypeDidChangeTo(map.getMapTypeId());
    });
    google.maps.event.addListener(map, "mousemove", function(e) {
        var p = e.latLng;
        qMapView.cursorDidMoveTo(p.lat(), p.lng());
        if(mouseDown && shiftIsPressed) {
            if(selectedArea != null) {
                bounds.extend(e.latLng);
                selectedArea.setBounds(bounds);
                qMapView.selectedAreaDidChangeTo(
                    bounds.getNorthEast().lat(), bounds.getSouthWest().lng(),
                    bounds.getSouthWest().lat(), bounds.getNorthEast().lng()
                );
            } else {
                bounds = new google.maps.LatLngBounds();
                bounds.extend(e.latLng);
                selectedArea = new google.maps.Rectangle({
                    map: map,
                    clickable: false,
                    editable: true,
                    strokeColor: "#FF0000",
                    strokeOpacity: 0.8,
                    fillColor: "#FF0000",
                    fillOpacity: 0.25
                });
                qMapView.selectedAreaWasCreated(
                    bounds.getNorthEast().lat(), bounds.getSouthWest().lng(),
                    bounds.getSouthWest().lat(), bounds.getNorthEast().lng()
                );
            }

        }
    });
    google.maps.event.addListener(map, "mousedown", function(e) {
        if(shiftIsPressed) {
            mouseDown = true;
            map.setOptions({draggable: false});
        }
    });
    google.maps.event.addListener(map, "mouseup", function(e) {
        if(mouseDown && shiftIsPressed) {
            mouseDown = false;
            map.setOptions({draggable: true});
            //selectedArea.setMap(null);
            //selectedArea = null;
        }
    });
    google.maps.event.addListener(map, "mouseover", function(e) {
        var p = e.latLng;
        qMapView.cursorDidEnterTo(p.lat(), p.lng());
    });
    google.maps.event.addListener(map, "mouseout", function(e) {
        var p = e.latLng;
        qMapView.cursorDidLeaveFrom(p.lat(), p.lng());
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

}

function keyUp(e)
{
    if(!e.shiftKey) {
        shiftIsPressed = false;
    }
}

function keyDown(e)
{
    if(e.shiftKey) {
        shiftIsPressed = true;
    }
}

window.addEventListener? document.addEventListener('keydown', keyDown) : document.attachEvent('keydown', keyDown);
window.addEventListener? document.addEventListener('keyup', keyUp) : document.attachEvent('keyup', keyUp);


function appendMarker(name, latitude, longitude)
{
    var marker = new google.maps.Marker({
        position: new google.maps.LatLng(latitude, longitude),
        map: map,
        title: name,
        animation: google.maps.Animation.DROP
    });

     google.maps.event.addListener(marker, "click", function() {
         var index = -1;
         for (var key in markers)
         {
             if (markers[key] === marker)
             {
                 index = key;
                 break;
             }
         }
         qMapView.onMarkerClicked(index);
     });

    markers[markerIndex] = marker;
    markerIndex++;

    return markerIndex - 1;
}

function getMapBounds()
{
    var bounds = map.getBounds();
    var ne = bounds.getNorthEast();
    var sw = bounds.getSouthWest();
    return {
        "north": ne.lng(),
        "south": sw.lng(),
        "east": ne.lat(),
        "west": sw.lat()
    };
}

function getMapCenter()
{
    var center = map.getCenter();
    return {
        "latitude": center.lat(),
        "longitude": center.lng()
    }
}

function setMapCenter(lat, lng, animated)
{
    var latlng = new google.maps.LatLng(lat, lng);
    if (animated)
        map.panTo(latlng);
    else
        map.setCenter(latlng);
}

function boundsFromCoordinates(north, south, east, west)
{
    var ne = new google.maps.LatLng(north, east);
    var sw = new google.maps.LatLng(south, west);
    return new google.maps.LatLngBounds(sw, ne);
}

function panMapToBounds(north, south, east, west)
{
    map.panToBounds(boundsFromCoordinates(north, south, east, west));
}

function fitMapToBounds(north, south, east, west)
{
    map.fitBounds(boundsFromCoordinates(north, south, east, west));
}
