package org.elsys.robocode;

import java.awt.Color;
import robocode.AdvancedRobot;
import robocode.HitRobotEvent;
import robocode.HitWallEvent;
import robocode.ScannedRobotEvent;
import robocode.util.Utils;

public class Tuesday extends AdvancedRobot {
	private boolean movingForward = true;
	
	@Override
	public void run() {
		setBodyColor(Color.PINK);
		setAhead(Double.POSITIVE_INFINITY);
		setAdjustRadarForRobotTurn(true);
		setAdjustGunForRobotTurn(true);
		setTurnRadarRight(Double.POSITIVE_INFINITY);
		
		while(true) {
			
			execute();
		}
	}
	
	private void reverseDirection() {
		if(movingForward) {
			movingForward = false;
			setBack(Double.POSITIVE_INFINITY);
		}else{
			movingForward = true;
			setAhead(Double.POSITIVE_INFINITY);
		}
	}
	
	@Override
	public void onHitWall(HitWallEvent event) {
		reverseDirection();
	}
	
	@Override
	public void onHitRobot(HitRobotEvent event) {
		reverseDirection();
	}
	
	@Override
	public void onScannedRobot(ScannedRobotEvent event) {
		double absoluteBearing = getHeadingRadians() + event.getBearingRadians();
		double radians = Utils.normalRelativeAngle(absoluteBearing - getGunHeadingRadians());
		setTurnGunRightRadians(radians);
		setTurnLeftRadians(radians);
	}
}
