#define PI 3.14159f

class Camera {
	public:
		float movementSpeed = 0.1f;
		float currentAngleXZ, currentAngleYZ;

		struct Vec3 {
			float x;
			float y;
			float z;
		};

		Vec3 origin;
		Vec3 eye, target, up;
		
		static float rad(float);
		float distance(float, float, float, float);

		Camera();
		void reset();

		void moveLeft();
		void moveRight();
		void moveUp();
		void moveDown();
		void zoomIn();
		void zoomOut();
		void roll();

		void rotateX(float);
		void rotateY(float);
		void rotateZ(float);
};