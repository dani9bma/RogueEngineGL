/*
 * @module Graphics
 * @project Skel Engine(https://github.com/dani9bma/SkelEngine)
 * @author Daniel Assunção
 * @Github https://github.com/dani9bma
 */

#include "GLScene.h"
#include "DXScene.h"

using namespace Skel;

int main(void)
{
#if SKEL_OPENGL
	Scene3DOpenGL* sceneOpengl = new Scene3DOpenGL();
#elif SKEL_DX
	DXScene* sceneDX = new DXScene();
}
#endif