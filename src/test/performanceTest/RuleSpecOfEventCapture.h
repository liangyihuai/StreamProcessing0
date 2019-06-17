#pragma once

#include <iostream>
#include <vector>

using namespace std;

string ef_rule1_name = "targetData";
string ef_rule1 = "If not duplicate(id) & not unusual(speed)\
		\r\nFrom rawData\
		\r\nThen targetData";

string ec_rule2_name = "EnemyTarget";
string ec_rule2 = "If target.iff = unknown\
		\r\nFrom targetData\
		\r\nThen EnemyTarget";

string cq_rule3_name = "flyingAllyTarget";
string cq_rule3 = "If speed > 500 & elevation > 200\
		\r\nFrom allytarget\
		\r\nThen flyingAllyTarget";

string cep_rule4_name = "cepTarget1";
string cep_rule4 = "If exist(flyingAllyTarget)\
		\r\nFrom flyingAllyTarget\
		\r\nThen cepTarget1";

string ec_rule5_name = "enemyTarget";
string ec_rule5 = "If target.iff = unknown\r\nFrom targetData\r\nThen enemyTarget";

string cq_rule6_name = "nearbyEnemyTarget";
string cq_rule6 = "If distance(127.12, 35.33)<0.52\r\nFrom enemyTarget\r\nThen nearbyEnemyTarget";

string cq_rule7_name = "flyingEnemyTarget";
string cq_rule7 = "If speed>500 & elevation > 200\r\nFrom enemyTarget\r\nThen flyingEnemyTarget";

string cep_rule8_name = "dangerousTarget";
string cep_rule8 = "If exist(nearbyEnemyTarget) & exist(flyingEnemyTarget)\
\r\nFrom nearbyEnemyTarget, flyingEnemyTarget\r\nThen dangerousTarget";

string cep_rule9_name = "cepTarget2";
string cep_rule9 = "If exist(enemyTarget) & exist(flyingAllyTarget)\
\r\nFrom enemyTarget, flyingAllyTarget\r\nThen cepTarget2";

string cq_enemy_aircraft_name = "EnemyAircraft";
string cq_enemy_aircraft = "IF ElevationAngle >30 & Speed > 150 & elevation > 100\
\r\nFROM EnemyTarget\
\r\nTHEN EnemyAircraft, objectType = aircraft";

string cq_enemy_distance_name = "EnemyDistance";
string cq_enemy_distance = "IF elevation > 10\
\r\nFROM EnemyTarget\
\r\nTHEN EnemyDistance, distance(127.12, 35.33)";

//
string cq_enemy_count = "IF elevation > 10\
\r\nFROM EnemyTarget\
\r\nWindow length=3000, sliding=1000, distinct=objId\
\r\nTHEN EnemyCount, count()";

string cq_enemy_count1_name = "enemycount1";
string cq_enemy_count1 = "If EnemyCount.count > 2 & EnemyDistance.distance >0.01\
\r\nFrom EnemyCount, EnemyDistance\
\r\nWindow length = 1000, sliding=1000\
\r\nThen enemycount1";


string cep_exist1 = "If exist(EnemyDistance) & exist(EnemyCount) & EnemyCount.count > 3 & EnemyDistance.distance > 0.3\
\r\nFrom EnemyCount, EnemyDistance\
\r\nWindow length=3000, sliding=1000\
\r\nThen cep_exist1";


