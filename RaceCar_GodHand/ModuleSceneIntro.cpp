#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "ModulePhysics3D.h"
#include "Primitive.h"
#include "PhysBody3D.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

    BuildCircuit();

	App->camera->Move(vec3(10.0f, 10.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
    // Render
    Plane p(0, 1, 0, 0);
    p.axis = true;
    p.Render();

    for (uint n = 0; n < c_circuit.Count(); n++)
    {
        c_circuit[n]->Render();
    }

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
}

void ModuleSceneIntro::BuildCircuit()
{
    const float size = 0.5f;
    const float height = 3.0f;
    const float pilonDistance = 0.3f;
    const float halfRoad = 10.0f;
    float previousRoadPos = 0.0f;
    p2Point<float> circleCenter;
    p2Point<float> roadPosition;

    roadPosition.x = 115.0f;
    roadPosition.y = 45.0f;
    previousRoadPos = CreateRoad(roadPosition, size, height, 15, pilonDistance, halfRoad, RoadType::VERTICAL_DOWN);

    circleCenter.x = 85.0f;
    circleCenter.y = previousRoadPos + roadPosition.y;
    CreateCurve(circleCenter, 30.0f, 90.0f, size, height, 35, pilonDistance, CurveType::BOTTOM_RIGHT);
    CreateCurve(circleCenter, 10.0f, 90.0f, size, height, 12, pilonDistance, CurveType::BOTTOM_RIGHT);

    roadPosition.x = circleCenter.x + 10.0f;
    roadPosition.y = previousRoadPos + 65.0f;
    previousRoadPos = CreateRoad(roadPosition, size, height, 50, pilonDistance, halfRoad, RoadType::HORIZONTAL_LEFT);

    circleCenter.x = 21.5f;
    circleCenter.y = -previousRoadPos - size;
    CreateCurve(circleCenter, 30.0f, 90.0f, size, height, 35, pilonDistance, CurveType::BOTTOM_LEFT);
    CreateCurve(circleCenter, 10.0f, 90.0f, size, height, 12, pilonDistance, CurveType::BOTTOM_LEFT);

    roadPosition.x = circleCenter.x - 10.0f;
    roadPosition.y = -previousRoadPos - size;
    previousRoadPos = CreateRoad(roadPosition, size, height * 3, 30, pilonDistance, halfRoad, RoadType::VERTICAL_UP);

    roadPosition.x = (halfRoad * 1.25f) - 1.0f;
    roadPosition.y = 27.0f;
    float positionY = -1.0f;
    CreateRamp(roadPosition, positionY, halfRoad * 1.85f, 20, RoadType::VERTICAL_UP);

    float xPos = 0.f;
    for (int n = 0; n < 14; n++)
    {
        Cylinder* c = new Cylinder(size, height);
        c->SetRotation(90.0f, { 0.0f,0.0f,1.0f });
        c_circuit.PushBack(c);
        c->SetPos(roadPosition.x - halfRoad + 1.5f + xPos, 0.f + height / 2, 2.0f);
        c->color = { 1,0.5,0,1 };
        App->physics->AddBody(*c, 0.0f);
        xPos += size + size + pilonDistance;
    }

    roadPosition.y = 2.0f;
    previousRoadPos = CreateRoad(roadPosition, size, height, 50, pilonDistance, halfRoad, RoadType::VERTICAL_UP);

    circleCenter.x = roadPosition.x - halfRoad * 3;
    circleCenter.y = previousRoadPos + size * 4;
    CreateCurve(circleCenter, 30.0f, 90.0f, size, height, 35, pilonDistance, CurveType::TOP_RIGHT);
    CreateCurve(circleCenter, 10.0f, 90.0f, size, height, 12, pilonDistance, CurveType::TOP_RIGHT);

    roadPosition.x = circleCenter.x + 10.0f;
    roadPosition.y = previousRoadPos - halfRoad * 2 + size * 4;
    previousRoadPos = CreateRoad(roadPosition, size, height, 25, pilonDistance, halfRoad, RoadType::HORIZONTAL_LEFT);

    circleCenter.x = previousRoadPos - 17.25f;
    circleCenter.y = roadPosition.y - (halfRoad * 2);
    CreateCurve(circleCenter, 30.0f, 90.0f, size, height, 35, pilonDistance, CurveType::BOTTOM_LEFT);
    CreateCurve(circleCenter, 10.0f, 90.0f, size, height, 12, pilonDistance, CurveType::BOTTOM_LEFT);

    circleCenter.x += previousRoadPos - 7.5f;
    CreateCurve(circleCenter, 30.0f, 90.0f, size, height, 35, pilonDistance, CurveType::TOP_RIGHT);
    CreateCurve(circleCenter, 10.0f, 90.0f, size, height, 12, pilonDistance, CurveType::TOP_RIGHT);

    roadPosition.x = circleCenter.x + 10.0f;
    roadPosition.y = previousRoadPos - (halfRoad * 9) - size;
    previousRoadPos = CreateRoad(roadPosition, size, height, 25, pilonDistance, halfRoad, RoadType::HORIZONTAL_LEFT);

    circleCenter.x = previousRoadPos - (halfRoad * 9) + size * 3;
    circleCenter.y = roadPosition.y + (halfRoad * 2);
    CreateCurve(circleCenter, 30.0f, 90.0f, size, height, 35, pilonDistance, CurveType::TOP_LEFT);
    CreateCurve(circleCenter, 10.0f, 90.0f, size, height, 12, pilonDistance, CurveType::TOP_LEFT);
    
    roadPosition.x = previousRoadPos - (halfRoad * 10) + size * 3;
    roadPosition.y = circleCenter.y + size * 3;
    previousRoadPos = CreateRoad(roadPosition, size, height, 72, pilonDistance, halfRoad, RoadType::VERTICAL_DOWN);

    circleCenter.x = roadPosition.x + (halfRoad);
    circleCenter.y = -previousRoadPos + (halfRoad * 8.5) + (size);
    CreateCurve(circleCenter, 30.0f, 90.0f, size, height, 35, pilonDistance, CurveType::BOTTOM_LEFT);
    CreateCurve(circleCenter, 10.0f, 90.0f, size, height, 12, pilonDistance, CurveType::BOTTOM_LEFT);

    roadPosition.x = roadPosition.x + halfRoad * 2;
    roadPosition.y = -previousRoadPos + (halfRoad * 10.5) + size;
    previousRoadPos = CreateRoad(roadPosition, size, height, 40, pilonDistance, halfRoad, RoadType::HORIZONTAL_RIGHT);
    
    roadPosition.x = -previousRoadPos - halfRoad + (size * 4);
    previousRoadPos = CreateRoad(roadPosition, size, height * 3, 40, pilonDistance, halfRoad, RoadType::HORIZONTAL_RIGHT);

    roadPosition.x = -9.5f;
    roadPosition.y = (halfRoad * 1.3f) - 1.1f;
    CreateRamp(roadPosition, positionY, halfRoad * 1.85f, 20, RoadType::HORIZONTAL_RIGHT);

    float zPos = 0.f;
    for (int n = 0; n < 14; n++)
    {
        Cylinder* c = new Cylinder(size, height);
        c->SetRotation(90.0f, { 0.0f,0.0f,1.0f });
        c_circuit.PushBack(c);
        c->SetPos(30.0f, 0.f + height / 2, roadPosition.y - halfRoad + 1.5f + zPos);
        c->color = { 1,0.5,0,1 };
        App->physics->AddBody(*c, 0.0f);
        zPos += size + size + pilonDistance;
    }

    roadPosition.x = previousRoadPos - (halfRoad * 2.0f) - (size * 4);
    previousRoadPos = CreateRoad(roadPosition, size, height, 51, pilonDistance, halfRoad, RoadType::HORIZONTAL_RIGHT);

    circleCenter.x = previousRoadPos + (halfRoad * 2) - (size * 3);
    circleCenter.y = roadPosition.y + (halfRoad * 2);
    CreateCurve(circleCenter, 30.0f, 90.0f, size, height, 35, pilonDistance, CurveType::TOP_RIGHT);
    CreateCurve(circleCenter, 10.0f, 90.0f, size, height, 12, pilonDistance, CurveType::TOP_RIGHT);

    roadPosition.x = 115.0f;
    roadPosition.y = 33.25f;
    previousRoadPos = CreateRoad(roadPosition, size, height, 9, pilonDistance, halfRoad, RoadType::VERTICAL_DOWN);
}

float ModuleSceneIntro::CreateRoad(p2Point<float> init, float sizePilon, float heightPilon, int numPilons, float pilonDistance, float halfRoad, RoadType type)
{
    float zPos = 0.f;
    float xPos = 0.f;
    switch (type)
    {
    case RoadType::VERTICAL_DOWN:
        {
            for (int n = 0; n < numPilons; n++)
            {
                Cylinder* c = new Cylinder(sizePilon, heightPilon);
                c->SetRotation(90.0f, { 0.0f,0.0f,1.0f });
                c_circuit.PushBack(c);
                c->SetPos(init.x + halfRoad, 0.f + heightPilon / 2, init.y + zPos);
                c->color = { 1,0.5,0,1 };
                App->physics->AddBody(*c, 0.0f);
                zPos += sizePilon + sizePilon + pilonDistance;
            }

            zPos = 0.f;
            for (int n = 0; n < numPilons; n++)
            {
                Cylinder* c = new Cylinder(sizePilon, heightPilon);
                c->SetRotation(90.0f, { 0.0f,0.0f,1.0f });
                c_circuit.PushBack(c);
                c->SetPos(init.x - halfRoad, 0.f + heightPilon / 2, init.y + zPos);
                c->color = { 1,0.5,0,1 };
                App->physics->AddBody(*c, 0.0f);
                zPos += sizePilon + sizePilon + pilonDistance;
            }
            return zPos;
            break;
        }
    case RoadType::HORIZONTAL_RIGHT:
        {
            for (int n = 0; n < numPilons; n++)
            {
                Cylinder* c = new Cylinder(sizePilon, heightPilon);
                c->SetRotation(90.0f, { 0.0f,0.0f,1.0f });
                c_circuit.PushBack(c);
                c->SetPos(init.x + xPos, 0.f + heightPilon / 2, init.y + halfRoad);
                c->color = { 1,0.5,0,1 };
                App->physics->AddBody(*c, 0.0f);
                xPos += sizePilon + sizePilon + pilonDistance;
            }

            xPos = 0.f;
            for (int n = 0; n < numPilons; n++)
            {
                Cylinder* c = new Cylinder(sizePilon, heightPilon);
                c->SetRotation(90.0f, { 0.0f,0.0f,1.0f });
                c_circuit.PushBack(c);
                c->SetPos(init.x + xPos, 0.f + heightPilon / 2, init.y - halfRoad);
                c->color = { 1,0.5,0,1 };
                App->physics->AddBody(*c, 0.0f);
                xPos += sizePilon + sizePilon + pilonDistance;
            }
            return xPos;
            break;
        }
    case RoadType::VERTICAL_UP:
        {
            for (int n = 0; n < numPilons; n++)
            {
                Cylinder* c = new Cylinder(sizePilon, heightPilon);
                c->SetRotation(90.0f, { 0.0f,0.0f,1.0f });
                c_circuit.PushBack(c);
                c->SetPos(init.x + halfRoad, 0.f + heightPilon / 2, init.y + zPos);
                c->color = { 1,0.5,0,1 };
                App->physics->AddBody(*c, 0.0f);
                zPos -= sizePilon + sizePilon + pilonDistance;
            }

            zPos = 0.f;
            for (int n = 0; n < numPilons; n++)
            {
                Cylinder* c = new Cylinder(sizePilon, heightPilon);
                c->SetRotation(90.0f, { 0.0f,0.0f,1.0f });
                c_circuit.PushBack(c);
                c->SetPos(init.x - halfRoad, 0.f + heightPilon / 2, init.y + zPos);
                c->color = { 1,0.5,0,1 };
                App->physics->AddBody(*c, 0.0f);
                zPos -= sizePilon + sizePilon + pilonDistance;
            }
            return zPos;
            break;
        }
    case RoadType::HORIZONTAL_LEFT:
        {
            for (int n = 0; n < numPilons; n++)
            {
                Cylinder* c = new Cylinder(sizePilon, heightPilon);
                c->SetRotation(90.0f, { 0.0f,0.0f,1.0f });
                c_circuit.PushBack(c);
                c->SetPos(init.x + xPos, 0.f + heightPilon / 2, init.y + halfRoad);
                c->color = { 1,0.5,0,1 };
                App->physics->AddBody(*c, 0.0f);
                xPos -= sizePilon + sizePilon + pilonDistance;
            }

            xPos = 0.f;
            for (int n = 0; n < numPilons; n++)
            {
                Cylinder* c = new Cylinder(sizePilon, heightPilon);
                c->SetRotation(90.0f, { 0.0f,0.0f,1.0f });
                c_circuit.PushBack(c);
                c->SetPos(init.x + xPos, 0.f + heightPilon / 2, init.y - halfRoad);
                c->color = { 1,0.5,0,1 };
                App->physics->AddBody(*c, 0.0f);
                xPos -= sizePilon + sizePilon + pilonDistance;
            }
            return xPos;
            break;
        }
    }

}

void ModuleSceneIntro::CreateCurve(p2Point<float> circleCenter, float radious, float referenceAngle, float sizePilon, float heightPilon, int numPilons, float pilonDistance, CurveType type)
{
    float ang = 0.0f;
    switch (type)
    {
    case CurveType::BOTTOM_LEFT:
        {
            for (int n = 0; n < numPilons; n++)
            {
                Cylinder* c = new Cylinder(sizePilon, heightPilon);
                c->SetRotation(90.0f, { 0.0f,0.0f,1.0f });
                c_circuit.PushBack(c);
                c->SetPos(circleCenter.x + 10.0f + (radious * -cos(DEGTORAD * ang)), 0.f + heightPilon / 2, circleCenter.y + (radious * sin(DEGTORAD * ang)));
                c->color = { 1,0.5,0,1 };
                App->physics->AddBody(*c, 0.0f);
                ang += referenceAngle / numPilons;
            }
            break;
        }
    case CurveType::BOTTOM_RIGHT:
        {
            for (int n = 0; n < numPilons; n++)
            {
                Cylinder* c = new Cylinder(sizePilon, heightPilon);
                c->SetRotation(90.0f, { 0.0f,0.0f,1.0f });
                c_circuit.PushBack(c);
                c->SetPos(circleCenter.x + 10.0f + (radious * cos(DEGTORAD * ang)), 0.f + heightPilon / 2, circleCenter.y + (radious * sin(DEGTORAD * ang)));
                c->color = { 1,0.5,0,1 };
                App->physics->AddBody(*c, 0.0f);
                ang += referenceAngle / numPilons;
            }
            break;
        }
    case CurveType::TOP_LEFT:
        {
            for (int n = 0; n < numPilons; n++)
            {
                Cylinder* c = new Cylinder(sizePilon, heightPilon);
                c->SetRotation(90.0f, { 0.0f,0.0f,1.0f });
                c_circuit.PushBack(c);
                c->SetPos(circleCenter.x + 10.0f + (radious * -cos(DEGTORAD * ang)), 0.f + heightPilon / 2, circleCenter.y + (radious * -sin(DEGTORAD * ang)));
                c->color = { 1,0.5,0,1 };
                App->physics->AddBody(*c, 0.0f);
                ang += referenceAngle / numPilons;
            }
            break;
        }
    case CurveType::TOP_RIGHT:
        {
            for (int n = 0; n < numPilons; n++)
            {
                Cylinder* c = new Cylinder(sizePilon, heightPilon);
                c->SetRotation(90.0f, { 0.0f,0.0f,1.0f });
                c_circuit.PushBack(c);
                c->SetPos(circleCenter.x + 10.0f + (radious * cos(DEGTORAD * ang)), 0.f + heightPilon / 2, circleCenter.y + (radious * -sin(DEGTORAD * ang)));
                c->color = { 1,0.5,0,1 };
                App->physics->AddBody(*c, 0.0f);
                ang += referenceAngle / numPilons;
            }
            break;
        }
    }
}

void ModuleSceneIntro::CreateRamp(p2Point<float> position, float height, float length, float angle, RoadType type)
{
    switch (type)
    {
    case RoadType::VERTICAL_DOWN:
        {
            Cube* r = new Cube(length, 5.0f, 5.0f);
            r->SetPos(position.x, height, position.y);
            r->SetRotation(-angle, { 1,0,0 });
            c_circuit.PushBack(r);
            r->color = { 0,0,1,1 };
            App->physics->AddBody(*r, 0.0f);
            break;
        }
    case RoadType::HORIZONTAL_RIGHT:
        {
            Cube* r = new Cube(5.0f, 5.0f, length);
            r->SetPos(position.x, height, position.y);
            r->SetRotation(angle, { 0,0,1 });
            c_circuit.PushBack(r);
            r->color = { 0,0,1,1 };
            App->physics->AddBody(*r, 0.0f);
            break;
        }
    case RoadType::VERTICAL_UP:
        {
            Cube* r = new Cube(length, 5.0f, 5.0f);
            r->SetPos(position.x, height, position.y);
            r->SetRotation(angle, { 1,0,0 });
            c_circuit.PushBack(r);
            r->color = { 0,0,1,1 };
            App->physics->AddBody(*r, 0.0f);
            break;
        }
    case RoadType::HORIZONTAL_LEFT:
        {
            Cube* r = new Cube(5.0f, 5.0f, length);
            r->SetPos(position.x, height, position.y);
            r->SetRotation(-angle, { 0,0,1 });
            c_circuit.PushBack(r);
            r->color = { 0,0,1,1 };
            App->physics->AddBody(*r, 0.0f);
            break;
        }
    }
}