#ifndef CONSTANTS
#define CONSTANTS

#define LENGTH 600
#define HEIGHT 700

#define BULLETWIDTH 13
#define MISSILEWIDTH 40
#define LASERWIDTH 90
#define LASERBALLWIDTH 100
#define WINGMANWIDTH 63
#define LIGHTINGBALLWIDTH 30
#define PLAYERWIDTH 92
#define ENEMYBULLET1WIDTH 30

enum GameObjectsData {
    GD_Type
};

enum GameObjectTypes {
    GO_PlayerPlane,
    GO_EnemyPlane,
    GO_PlayerBullet,
    GO_EnemyBullet,
    GO_PlayerLaser,
    GO_BuffItem,
    GO_PlayerMissile,
    GO_PlayerLightingBall,
    GO_EnemyBoss
};

enum BuffType {
    TurnToBullet,
    TurnToLaser,
    LevelUp,
    AddMissile,
    Diamond
};

enum Direction{
    UpLeft,
    UpRight,
    DownLeft,
    DownRight,
    Left,
    Right,
    Up,
    Down
};

enum AttackType{
    Bullet,
    Laser
};




#endif // CONSTANTS

