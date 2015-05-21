#include "ThighJoint.h"

#include "../Primitives/Quad.h"
#include "Dimensions.h"

using ModernGDV::Vertex;
using Geometries::Primitives::Quad;
using glm::vec3;
using glm::vec2;


Geometries::Robot::ThighJoint::ThighJoint(ModernGDV::Driver* mgdv)
: mgdv(mgdv), vertexBuffer(0U), texture(nullptr)
{
	std::vector<Vertex> vertices;

	//Vorderquader
	vec3 fCuboidBottomFrontLeft		( +0.0f,			-0.5f * Dim::THJ_HEIGHT, +0.5 * Dim::THJ_DEPTH );
	vec3 fCuboidBottomFrontRight	( Dim::THJ_WIDTH,	-0.5f * Dim::THJ_HEIGHT, +0.5 * Dim::THJ_DEPTH );
	vec3 fCuboidBottomBackLeft		( +0.0f,			-0.5f * Dim::THJ_HEIGHT, +0.5 * Dim::THJ_IDEPTH );
	vec3 fCuboidBottomBackRight		( Dim::THJ_WIDTH,	-0.5f * Dim::THJ_HEIGHT, +0.5 * Dim::THJ_IDEPTH );
	vec3 fCuboidTopFrontLeft		( +0.0f,			+0.5f * Dim::THJ_HEIGHT, +0.5 * Dim::THJ_DEPTH );
	vec3 fCuboidTopFrontRight		( Dim::THJ_WIDTH,	+0.5f * Dim::THJ_HEIGHT, +0.5 * Dim::THJ_DEPTH );
	vec3 fCuboidTopBackLeft			( +0.0f,			+0.5f * Dim::THJ_HEIGHT, +0.5 * Dim::THJ_IDEPTH );
	vec3 fCuboidTopBackRight		( Dim::THJ_WIDTH,	+0.5f * Dim::THJ_HEIGHT, +0.5 * Dim::THJ_IDEPTH );


	//Hinterquader
	vec3 bCuboidBottomFrontLeft		( +0.0f,			-0.5f * Dim::THJ_HEIGHT, -0.5 * Dim::THJ_IDEPTH );
	vec3 bCuboidBottomFrontRight	( Dim::THJ_WIDTH,	-0.5f * Dim::THJ_HEIGHT, -0.5 * Dim::THJ_IDEPTH );
	vec3 bCuboidBottomBackLeft		( +0.0f,			-0.5f * Dim::THJ_HEIGHT, -0.5 * Dim::THJ_DEPTH );
	vec3 bCuboidBottomBackRight		( Dim::THJ_WIDTH,	-0.5f * Dim::THJ_HEIGHT, -0.5 * Dim::THJ_DEPTH );
	vec3 bCuboidTopFrontLeft		( +0.0f,			+0.5f * Dim::THJ_HEIGHT, -0.5 * Dim::THJ_IDEPTH );
	vec3 bCuboidTopFrontRight		( Dim::THJ_WIDTH,	+0.5f * Dim::THJ_HEIGHT, -0.5 * Dim::THJ_IDEPTH );
	vec3 bCuboidTopBackLeft			( +0.0f,			+0.5f * Dim::THJ_HEIGHT, -0.5 * Dim::THJ_DEPTH );
	vec3 bCuboidTopBackRight		( Dim::THJ_WIDTH,	+0.5f * Dim::THJ_HEIGHT, -0.5 * Dim::THJ_DEPTH );

	//Mittelquader
	vec3 mCuboidBottomFrontLeft		( +0.0f,			-0.5f * Dim::THJ_HEIGHT, +0.5 * Dim::THJ_IDEPTH );
	vec3 mCuboidBottomFrontRight	( Dim::THJ_IWIDTH,	-0.5f * Dim::THJ_HEIGHT, +0.5 * Dim::THJ_IDEPTH );
	vec3 mCuboidBottomBackLeft		( +0.0f,			-0.5f * Dim::THJ_HEIGHT, -0.5 * Dim::THJ_IDEPTH );
	vec3 mCuboidBottomBackRight		( Dim::THJ_IWIDTH,	-0.5f * Dim::THJ_HEIGHT, -0.5 * Dim::THJ_IDEPTH );
	vec3 mCuboidTopFrontLeft		( +0.0f,			+0.5f * Dim::THJ_HEIGHT, +0.5 * Dim::THJ_IDEPTH );
	vec3 mCuboidTopFrontRight		( Dim::THJ_IWIDTH,	+0.5f * Dim::THJ_HEIGHT, +0.5 * Dim::THJ_IDEPTH );
	vec3 mCuboidTopBackLeft			( +0.0f,			+0.5f * Dim::THJ_HEIGHT, -0.5 * Dim::THJ_IDEPTH );
	vec3 mCuboidTopBackRight		( Dim::THJ_IWIDTH,	+0.5f * Dim::THJ_HEIGHT, -0.5 * Dim::THJ_IDEPTH );

	Quad::Create( vertices, fCuboidBottomFrontLeft, vec2( 0.f, 0.f ), fCuboidBottomFrontRight, vec2( 1.f, 0.f ),
		fCuboidBottomBackRight, vec2( 1.f, 5.f/18.75f ), fCuboidBottomBackLeft, vec2( 0.f, 5.f/18.75f ) );
	Quad::Create( vertices, fCuboidTopFrontLeft, vec2( 0.f, 0.f ), fCuboidTopFrontRight, vec2( 1.f, 0.f ),
		fCuboidBottomFrontRight, vec2( 1.f, 10.f/18.75f ), fCuboidBottomFrontLeft, vec2( 0.f, 10.f/18.75f ) );
	Quad::Create( vertices, fCuboidTopFrontRight, vec2( 0.f, 0.f ), fCuboidTopBackRight, vec2( 5.f/10.f, 0.f ),
		fCuboidBottomBackRight, vec2( 5.f/10.f, 1.f ), fCuboidBottomFrontRight, vec2( 0.f, 1.f ) );
	Quad::Create( vertices, fCuboidTopBackRight, vec2( 0.f, 0.f ), fCuboidTopBackLeft, vec2( 1.f, 0.f ),
		fCuboidBottomBackLeft, vec2( 1.f, 10.f/18.75f ), fCuboidBottomBackRight, vec2( 0.f, 10.f/18.75f ) );
	Quad::Create( vertices, fCuboidTopBackLeft, vec2( 0.f, 0.f ), fCuboidTopFrontLeft, vec2( 5.f/10.f, 0.f ),
		fCuboidBottomFrontLeft, vec2( 5.f/10.f, 1.f ), fCuboidBottomBackLeft, vec2( 0.f, 1.f ) );
	Quad::Create( vertices, fCuboidTopFrontLeft, vec2( 0.f, 5.f/18.75f ), fCuboidTopBackLeft, vec2( 0.f, 0.f ),
		fCuboidTopBackRight, vec2( 1.f, 0.f ), fCuboidTopFrontRight, vec2( 1.f, 5.f/18.75f ) );

	Quad::Create( vertices, mCuboidBottomFrontLeft, vec2( 0.f, 0.f ), mCuboidBottomFrontRight, vec2( 5.f/15.f, 0.f ),
		mCuboidBottomBackRight, vec2( 5.f/15.f, 1.f ), mCuboidBottomBackLeft, vec2( 0.f, 1.f ) );
	Quad::Create( vertices, mCuboidTopFrontRight, vec2( 0.f, 0.f ), mCuboidTopBackRight, vec2( 1.f, 0.f ),
		mCuboidBottomBackRight, vec2( 1.f, 10.f/15.f ), mCuboidBottomFrontRight, vec2( 0.f, 10.f/15.f ) );
	Quad::Create( vertices, mCuboidTopBackLeft, vec2( 0.f, 0.f ), mCuboidTopFrontLeft, vec2( 1.f, 0.f ),
		mCuboidBottomFrontLeft, vec2( 1.f, 10.f/15.f ), mCuboidBottomBackLeft, vec2( 0.f, 10.f/15.f ) );
	Quad::Create( vertices, mCuboidTopFrontLeft, vec2( 0.f, 1.f ), mCuboidTopBackLeft, vec2( 0.f, 0.f ),
		mCuboidTopBackRight, vec2( 5.f/15.f, 0.f ), mCuboidTopFrontRight, vec2( 5.f/15.f, 1.f ) );

	Quad::Create(vertices, bCuboidBottomFrontLeft, vec2(0.f, 0.f), bCuboidBottomFrontRight, vec2(1.f, 0.f),
		bCuboidBottomBackRight, vec2(1.f, 5.f / 18.75f), bCuboidBottomBackLeft, vec2(0.f, 5.f / 18.75f));
	Quad::Create(vertices, bCuboidTopFrontLeft, vec2(0.f, 0.f), bCuboidTopFrontRight, vec2(1.f, 0.f),
		bCuboidBottomFrontRight, vec2(1.f, 10.f / 18.75f), bCuboidBottomFrontLeft, vec2(0.f, 10.f / 18.75f));
	Quad::Create(vertices, bCuboidTopFrontRight, vec2(0.f, 0.f), bCuboidTopBackRight, vec2(5.f / 10.f, 0.f),
		bCuboidBottomBackRight, vec2(5.f / 10.f, 1.f), bCuboidBottomFrontRight, vec2(0.f, 1.f));
	Quad::Create(vertices, bCuboidTopBackRight, vec2(0.f, 0.f), bCuboidTopBackLeft, vec2(1.f, 0.f),
		bCuboidBottomBackLeft, vec2(1.f, 10.f / 18.75f), bCuboidBottomBackRight, vec2(0.f, 10.f / 18.75f));
	Quad::Create(vertices, bCuboidTopBackLeft, vec2(0.f, 0.f), bCuboidTopFrontLeft, vec2(5.f / 10.f, 0.f),
		bCuboidBottomFrontLeft, vec2(5.f / 10.f, 1.f), bCuboidBottomBackLeft, vec2(0.f, 1.f));
	Quad::Create(vertices, bCuboidTopFrontLeft, vec2(0.f, 5.f / 18.75f), bCuboidTopBackLeft, vec2(0.f, 0.f),
		bCuboidTopBackRight, vec2(1.f, 0.f), bCuboidTopFrontRight, vec2(1.f, 5.f / 18.75f));


	vertexBuffer = mgdv->CreateVertexBuffer(vertices);

	texture = mgdv->GetTexture("Joint");


}

Geometries::Robot::ThighJoint::~ThighJoint()
{

}

void Geometries::Robot::ThighJoint::Render()
{
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	Vertex::SetLayout();
	mgdv->ShaderLib.SetDiffuseTex(texture);
	unsigned char index = 0U;

	index = Quad::Draw(index);
	index = Quad::Draw(index);
	index = Quad::Draw(index);
	index = Quad::Draw(index);
	index = Quad::Draw(index);
	index = Quad::Draw(index);

	index = Quad::Draw(index);
	index = Quad::Draw(index);
	index = Quad::Draw(index);
	index = Quad::Draw(index);

	index = Quad::Draw(index);
	index = Quad::Draw(index);
	index = Quad::Draw(index);
	index = Quad::Draw(index);
	index = Quad::Draw(index);
	index = Quad::Draw(index);

	Vertex::ResetLayout();
}

