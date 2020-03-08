#include <glm/glm.hpp>

class Camera {
	public:
		float movementSpeed = 0.1f;
		glm::vec3 eye, target, up, direction, xPosAxis, yPosAxis;

		Camera();
		void reset();
		void moveLeft();
		void moveRight();
		void moveUp();
		void moveDown();
		void zoomIn();
		void zoomOut();
};