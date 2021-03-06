
// SolarSystemView.h : interface of the CSolarSystemView class
//

#pragma once

#include <GL\glew.h>
#include <gl\gl.h>      // OpenGL Libraries
#include <gl\glu.h>     // GLU OpenGL Libraries

#include <glm.hpp>

#include "Camera.h"

#include "Program.h"
#include "SkyBoxCubeMapProgram.h"
#include "ShadowCubeMapProgram.h"
#include "Sphere.h"

#include "SolarSystemBodies.h"
#include "SolarSystemGLProgram.h"

class CSolarSystemDoc;


class CSolarSystemView : public CView
{
protected: // create from serialization only
	CSolarSystemView();
	DECLARE_DYNCREATE(CSolarSystemView)

// Attributes
public:
	CSolarSystemDoc* GetDocument() const;

// Operations
public:

private:
	HGLRC m_hRC;     // Rendering Context
	HDC m_hDC;       // Device Context
	CPalette m_GLPalette;   // Logical Palette
	UINT_PTR timer;

	int Width, Height;

	int wheelAccumulator;

	OpenGL::Camera camera;

	glm::mat4 perspectiveMatrix;

	SolarSystemGLProgram *program;

	OpenGL::Sphere *sphere;
	
	OpenGL::SkyBoxCubeMapProgram *skyBoxProgram;
	OpenGL::ShadowCubeMapProgram *shadowProgram;



	class Uniforms {
	public:
		Uniforms(SolarSystemBodies& m_SolarSystem, SolarSystemGLProgram& program, unsigned int nrlights);
	};

	class ShadowUniforms {
	public:
		ShadowUniforms(SolarSystemBodies& m_SolarSystem, OpenGL::ShadowCubeMapProgram& program, unsigned int nrlights);
	};
	
	
	bool keyDown;
	bool ctrl;
	bool shift;
	OpenGL::Camera::Movements movement;

	bool inited;

	void InitializePalette(void);

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CSolarSystemView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

private:
	void RenderScene();
	void RenderShadowScene();
	void RenderSkybox();

	void Resize(GLsizei h, GLsizei w);
	
	void MoonHack(BodyPropList::iterator& pit, BodyList::iterator& it, glm::vec3& pos);

	Vector3D<double> GetTowardsVector(CPoint& point, const Vector3D<double>& forward);

	bool SetupShaders();
	bool SetupSkyBox();
	bool SetupShadows();
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg BOOL OnQueryNewPalette();
	afx_msg void OnPaletteChanged(CWnd* pFocusWnd);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	bool KeyPressHandler(MSG* pMsg);
	afx_msg void OnTimer(UINT_PTR nIDEvent);


	void Setup();
	void Reset();

	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	void ClearProgram();
	void ClearSkyBoxProgram();
	void ClearShadowProgram();
	void SetSpeeds(double translate, double rotate);
};

#ifndef _DEBUG  // debug version in SolarSystemView.cpp
inline CSolarSystemDoc* CSolarSystemView::GetDocument() const
   { return reinterpret_cast<CSolarSystemDoc*>(m_pDocument); }
#endif

