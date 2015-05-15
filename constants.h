#ifndef CONSTANTS
#define CONSTANTS

#define LENGTH 600
#define HEIGHT 800

#define BULLETWIDTH 13
#define MISSILEWIDTH 40
#define LASERWIDTH 20
#define WINGMANWIDTH 63
#define LIGHTINGBALLWIDTH 30
#define PLAYERWIDTH 92

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
    GO_PlayerLightingBall
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

