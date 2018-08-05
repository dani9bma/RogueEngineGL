/*
* @module Graphics
* @project Skel Engine(https://github.com/dani9bma/SkelEngine)
* @author Daniel Assunção
* @Github https://github.com/dani9bma
*/




void GarroshVisible()
{
	garrosh->setVisibility(true);
}

void GarroshInvisible()
{
	garrosh->setVisibility(false);
}

void SponzaVisible()
{
	sponza->setVisibility(true);
}

void SponzaInvisible()
{
	sponza->setVisibility(false);
}

void CrysisVisible()
{
	crysis->setVisibility(true);
}

void CrysisInvisible()
{
	crysis->setVisibility(false);
}


namespace Skel
{
	class SKEL_API Scene3DOpenGL
	{
	public:

		Scene3DOpenGL()
		{

		}
	};
}