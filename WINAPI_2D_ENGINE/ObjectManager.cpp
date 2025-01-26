#include "ObjectManager.h"

VOID GAME::ObjectManager::Initialize()
{

    //�� ������Ʈ �޸��忡�� ��ǥ �ҷ��ͼ� �а� �Ұ�(ü��ȭ)
    std::ifstream Load_Point; // object ��ǥ
    FLOAT Pos_x, Pos_y, width, height; // object �Ӽ�
    Load_Point.open("Resources\\BlockPoint.txt"); // �޸��� ���� ����
    UINT Obj_Index= 0, Obj_Type = 0;;

    //point_x,point_y,width,height,obj_Type
    while (!Load_Point.eof())
    {
        Load_Point >> Obj_Type;
        switch (Obj_Type)
        {
        case  ObjectType::Ground_Obj:
        case ObjectType::Block_Obj:
        case ObjectType::Ceiling_Obj:
            Object_list.push_back(new Block);
            break;
        case ObjectType::Door_Obj:
            Object_list.push_back(new Door);
            break;
        }
      
        Load_Point >> Pos_x;
        Load_Point >> Pos_y;
        Load_Point >> width;
        Load_Point >> height;
        Object_list[Obj_Index]->Initialize(Pos_x, Pos_y, width, height, Obj_Type);
        Obj_Index++;
    }


}

VOID GAME::ObjectManager::Release()
{
    for (Object* Obj : Object_list)
    {
        REL_DEL(Obj);
    }
}

VOID GAME::ObjectManager::Update(const FLOAT& deltaTime)
{
    for (Object* Obj : Object_list)
    {
        Obj->Update(deltaTime);
    }
}

VOID GAME::ObjectManager::Draw()
{
    for (Object* Obj : Object_list)
    {
        Obj->Draw();
    }
}



