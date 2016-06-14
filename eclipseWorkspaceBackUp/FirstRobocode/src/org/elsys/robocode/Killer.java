package org.elsys.robocode;

import robocode.Robot;
import robocode.ScannedRobotEvent;

public class Killer extends Robot {

	@Override
	public void run() {
		while (true) {
			turnLeft(30);
		}
	}

	@Override
	public void onScannedRobot(ScannedRobotEvent event) {
		double fire = (getBattleFieldWidth() / event.getDistance()) * (getEnergy() / 10);
		fire(fire);
		turnLeft(10);
		fire(fire);
		turnRight(20);
		fire(fire);
		ahead(event.getDistance() / 3);
	}

}