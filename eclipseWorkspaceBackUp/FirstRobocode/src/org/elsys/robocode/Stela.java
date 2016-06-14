package org.elsys.robocode;

import robocode.Robot;
import robocode.ScannedRobotEvent;

public class Stela extends Robot {
	@Override
	public void run() {
		while(true) {
			turnGunLeft(30);
		}
	}
	
	@Override
	public void onScannedRobot(ScannedRobotEvent event) {
		ahead(event.getDistance() / 2);
		double fire = (getBattleFieldWidth() / event.getDistance()) * (event.getEnergy() / 20);
		fire(fire);
		turnLeft(10);
		fire(fire);
		turnRight(20);
		fire(fire);
	}
	
}
