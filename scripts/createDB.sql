create table IF NOT EXISTS searches(searchID text primary key, startTime text, area text, height integer,
					gimballAngle integer, fpsProcessing integer);

create table IF NOT EXISTS drones(droneID text primary key, dronePort integer, visionWidth integer,
				streamPort integer, controllerIP text, droneIP text,  streamPath text);

create table IF NOT EXISTS dronessearches(searchID text, droneID text, path text,
		foreign key(searchID) references searches(searchID),
		foreign key(droneID) references drones(droneID));

create table IF NOT EXISTS videosequences(videoID text primary key, searchID text, droneID text,
				start text, end text, frameCount integer, path text,
				foreign key(searchID) references searches(searchID),
                		foreign key(droneID) references drones(droneID));

create table IF NOT EXISTS detectionresults(searchID text, droneID text,
				latitude integer, longitude integer, score integer,
				foreign key(searchID) references searches(searchID),
                                foreign key(droneID) references drones(droneID));

create table IF NOT EXISTS statuses(droneID text, timestampDrone text,
			timestampReceivedWorkstation text, latitude integer, longitude integer,
			orientation integer, cameraAngle integer, speed integer,
			selectedSpeed integer, height integer, selectedHeight integer,
			batteryLevel integer, fps integer, resolution integer,
			heartbeat integer, droneState integer, manufacturer text,
                        droneType text, nextWaypointLongitude integer, nextWaypointLatitude integer,
			previousWaypointOrder integer,
			nextWaypoints text,
                        foreign key(droneID) references drones(droneID));
