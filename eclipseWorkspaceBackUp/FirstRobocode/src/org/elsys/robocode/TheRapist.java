package org.elsys.robocode;

import robocode.AdvancedRobot;
import robocode.HitByBulletEvent;
import robocode.HitRobotEvent;
import robocode.HitWallEvent;
import robocode.Rules;
import robocode.ScannedRobotEvent;
import robocode.util.Utils;

public class TheRapist extends AdvancedRobot {
	private int directionToMove = 1;
	private double enemyEnergy = 100.0;
	private double fieldWidth = 0.0;

	@Override
	public void run() {
		setAdjustRadarForRobotTurn(true);
		setAdjustGunForRobotTurn(true);
		setTurnRadarRight(Double.POSITIVE_INFINITY);
		setAhead(Double.POSITIVE_INFINITY);
		fieldWidth = getBattleFieldWidth();
	}

	@Override
	public void onScannedRobot(ScannedRobotEvent event) {
		setTurnRight(event.getBearing() + 90 - 30 * directionToMove);
		
		double distance = event.getDistance();
		double energyDiff = enemyEnergy - event.getEnergy();
		if (energyDiff > 0 && energyDiff <= 3) {
			if(distance > fieldWidth / 2.5) {
				directionToMove = -directionToMove;
				setAhead((distance / 2) * directionToMove * 1.5);
		
			}else{
				directionToMove = -directionToMove;
				setAhead((distance / 2) * directionToMove);
			}
		}
	
		distance = event.getDistance();
		double absoluteBearing = getHeadingRadians() + event.getBearingRadians();
		double radians = Utils.normalRelativeAngle(absoluteBearing - getGunHeadingRadians());
		setTurnGunRightRadians(radians);
		setTurnLeftRadians(radians);
		if (distance <= fieldWidth / 2) {
			double fire = (fieldWidth / distance) * (getEnergy() / 10);
			fire(fire);
		}else{
			fire(0.8);
		}
		enemyEnergy = event.getEnergy();
	}

	@Override
	public void onHitByBullet(HitByBulletEvent event) {
		setTurnRight(90);
		setAhead(50);
	}

	@Override
	public void onHitRobot(HitRobotEvent event) {
		setBack(50);
	}

	@Override
	public void onHitWall(HitWallEvent event) {
		setTurnRight(90);
		setAhead(50);
	}

}
