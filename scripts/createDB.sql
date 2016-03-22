create table IF NOT EXISTS searches(searchID text primary key, start text);

create table IF NOT EXISTS drones(droneID text primary key, visionWidth integer);

create table IF NOT EXISTS dronessearches(searchID text, droneID text, path text,
		foreign key(searchID) references searches(searchID),
		foreign key(droneID) references drones(droneID));

create table IF NOT EXISTS videosequences(videoID text primary key, searchID text, droneID text,
				start text, end text, frameCount integer, path text,
				foreign key(searchID) references searches(searchID),
                		foreign key(droneID) references drones(droneID));

create table IF NOT EXISTS detectionresults(videoID text, searchID text, droneID text,
				latitude integer, longitude integer, score integer,
				foreign key(searchID) references searches(searchID),
                                foreign key(droneID) references drones(droneID),
				foreign key(videoID) references videosequences(videoID));

create table IF NOT EXISTS statuses(searchID text, droneID text, timestampDrone text, timestampWorkstation
			text, latitude integer, longitude integer, altitude integer, orientation
			integer, gimballAngle integer, speed integer, batteryLevel integer,
			droneState integer, foreign key(searchID) references searches(searchID),
                        foreign key(droneID) references drones(droneID));
