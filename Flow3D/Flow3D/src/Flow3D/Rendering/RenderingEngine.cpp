#include "RenderingEngine.hpp"

#include "Flow3D/Log.hpp"
#include "Flow3D/Math.hpp"

#include "Flow3D/Components/FreeCamera.hpp"

#include "Texture.hpp"

namespace Flow {

	RenderingEngine::RenderingEngine(const Window& window)
		: m_Window(&window)
	{
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_MULTISAMPLE);
		// every Model will determine if GL_BLEND needs to be enabled: glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// framebuffer configuration
   // -------------------------
		glGenFramebuffers(1, &m_Framebuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, m_Framebuffer);
		// create a color attachment texture
		glGenTextures(1, &m_RenderTexture);
		glBindTexture(GL_TEXTURE_2D, m_RenderTexture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Window->GetWidth(), m_Window->GetHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_RenderTexture, 0);
		// create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
		unsigned int rbo;
		glGenRenderbuffers(1, &rbo);
		glBindRenderbuffer(GL_RENDERBUFFER, rbo);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_Window->GetWidth(), m_Window->GetHeight()); // use a single renderbuffer object for both a depth AND stencil buffer.
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo); // now actually attach it
		// now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			FLOW_CORE_ERROR("ERROR::FRAMEBUFFER:: Framebuffer is not complete!");
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void RenderingEngine::Render(const GameObject& root, GameObject& mainCamera, const Skybox& skybox)
	{
		// bind to framebuffer and draw scene as we normally would to color texture 
		glBindFramebuffer(GL_FRAMEBUFFER, m_Framebuffer);
		glEnable(GL_DEPTH_TEST);

		viewPosition = mainCamera.GetTransform()->GetWorldPosition();
		// when beginning to render clear everything
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// receive the view matrix from the current main camera
		Mat4 view = mainCamera.GetComponent<FreeCamera>().GetViewMatrix();

		// get the projection matrix
		Mat4 projection = Mat4();
		projection = Mat4::GetPerspectiveProjection(Math::Radians(mainCamera.GetComponent<FreeCamera>().GetZoom()), (float)m_Window->GetWidth() / (float)m_Window->GetHeight(), 0.1f, 100.0f);

		// render the scene starting with the scenes root object which contains all scene objects
		root.Render(view, projection, *this);
		//skybox.Draw(view, projection);

		// now bind back to default framebuffer and draw a quad plane with the attached framebuffer color texture
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glDisable(GL_DEPTH_TEST);

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void RenderingEngine::SetBlending(bool blending)
	{
		if (blending)
			glEnable(GL_BLEND);
		else
			glDisable(GL_BLEND);
	}
}