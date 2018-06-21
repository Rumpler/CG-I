
#ifndef _H_Ball
#define _H_Ball


#include <vector>

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>


class CgTrackball   {

 public: 

    CgTrackball();

    void init(const glm::mat4& m = glm::mat4(1.));
    void place(const glm::vec3& center, float radius);
    const glm::mat4& getRotationMatrix();

    void beginDrag();
    void endDrag();

    void Ball_Mouse(glm::vec3 vNow);
    void Ball_Update();

private:
	


	glm::vec3 MouseOnSphere(glm::vec3 mouse, glm::vec3 ballCenter, float ballRadius);
	void Qt_ToBallPoints(glm::quat q, glm::vec3 *arcFrom, glm::vec3 *arcTo);

	glm::vec3 ConstrainToAxis(glm::vec3 loose, glm::vec3 axis);
	unsigned int NearestConstraintAxis(glm::vec3 loose, std::vector<glm::vec3> axes);
	


	glm::vec3 center;
	float radius;

	glm::vec3 vNow, vDown, vFrom, vTo, vrFrom, vrTo;
	bool showResult, dragging;

	glm::mat4 mNow,mDown;
	glm::quat qNow, qDown, qDrag;



}; 

#endif
