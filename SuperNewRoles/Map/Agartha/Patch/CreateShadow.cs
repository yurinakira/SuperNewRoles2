using PowerTools;
using System;
using System.Collections.Generic;
using System.Text;
using UnityEngine;

namespace SuperNewRoles.Map.Agartha.Patch
{
    public static class CreateShadow
    {
        public static void Create(Transform Miraship)
        {
            Transform Cafe = Miraship.FindChild("Cafe").FindChild("Shadows");
            int i = 0;
            foreach (EdgeCollider2D col in Cafe.GetComponents<EdgeCollider2D>())
            {
                i++;
                if (i < 5)
                {
                    GameObject.Destroy(col);
                }
            }
            Cafe.gameObject.SetActive(true);
            EdgeCollider2D CafeCol = Cafe.gameObject.AddComponent<EdgeCollider2D>();
            CafeCol.points = new Vector2[] { new Vector2(1f, 4.95f), new Vector2(3.85f, 4.95f), new Vector2(3.85f, -5.45f), new Vector2(-3.665f, -5.45f), new Vector2(-3.65f, -1.8f) };
            EdgeCollider2D CafeCol2 = Cafe.gameObject.AddComponent<EdgeCollider2D>();
            CafeCol2.points = new Vector2[] { new Vector2(-3.65f, 0.785f), new Vector2(-3.65f, 2.8f), new Vector2(-1.4f, 5f), new Vector2(-0.3f, 5f) };

            EdgeCollider2D ElecCol = Cafe.gameObject.AddComponent<EdgeCollider2D>();
            ElecCol.points = new Vector2[] { new Vector2(10.5f, 5.1f),new Vector2(10.5f, 4.7f), new Vector2(11.6f, 4.7f), new Vector2(11.6f, -5f),
                new Vector2(11.6f, -13.53f), new Vector2(9.45f, -13.53f) };
            EdgeCollider2D ElecCol2 = Cafe.gameObject.AddComponent<EdgeCollider2D>();
            ElecCol2.points = new Vector2[] { new Vector2(10.2f, -5f), new Vector2(5.05f, -5f), new Vector2(5.05f, 4.75f), new Vector2(8.725f, 4.75f), new Vector2(8.725f, 5.1f) };

            EdgeCollider2D LaboCol = Cafe.gameObject.AddComponent<EdgeCollider2D>();
            LaboCol.points = new Vector2[] { new Vector2(8.45f, -13.53f), new Vector2(6f, -13.53f), new Vector2(6f, -11.4f), new Vector2(4.8f, -11.4f), new Vector2(4.8f, -12.7f), new Vector2(1.55f, -12.7f), new Vector2(1.55f, -7.7f), new Vector2(4.45f, -7.7f), new Vector2(5.25f, -8.5f), new Vector2(5.25f, -9.4f), new Vector2(6.025f, -9.4f), new Vector2(6.025f, -5.75f), new Vector2(10.35f, -5.75f), new Vector2(10.35f, -5f) };

            //EdgeCollider2D CafeAisleCol1 = Cafe.gameObject.AddComponent<EdgeCollider2D>();
            //CafeAisleCol1.points = new Vector2[] { new Vector2(-3.65f, 0.785f), new Vector2(-5.15f, 0.785f), new Vector2(-5.15f, 5.7f), new Vector2(-0.85f, 5.7f), new Vector2(-0.85f, 5f) };
            
            EdgeCollider2D AdminAisleCol1 = Cafe.gameObject.AddComponent<EdgeCollider2D>();
            AdminAisleCol1.points = new Vector2[] {  new Vector2(-5.15f, -9.33f), new Vector2(-3.75f, -9.33f), new Vector2(-3.775f, -8.5f), new Vector2(-2.95f, -7.7f), new Vector2(-0.1f, -7.7f), new Vector2(-0.1f, -12.8f), new Vector2(-3.75f, -12.8f), new Vector2(-3.75f, -11.8f), new Vector2(-5.04f, -11.8f) };

            //通信室
            EdgeCollider2D CommsCol = Cafe.gameObject.AddComponent<EdgeCollider2D>();
            CommsCol.points = new Vector2[] {
                new Vector2(-13.7f,4.3f),new Vector2(-16.4f,4.3f),new Vector2(-16.4f,8.295f),new Vector2(-10.65f,8.295f),new Vector2(-10.65f,4.3f),new Vector2(-12.6f,4.3f)
            };

            //医務室
            EdgeCollider2D MedicalCol = Cafe.gameObject.AddComponent<EdgeCollider2D>();
            MedicalCol.points = new Vector2[] {
                new Vector2(-14f,0f),new Vector2(-17f,0f),new Vector2(-17f,-4f),new Vector2(-10.15f,-4f),new Vector2(-10.15f,0f),new Vector2(-12.2f,0f)
            };

            //O2
            EdgeCollider2D O2Col = Cafe.gameObject.AddComponent<EdgeCollider2D>();
            O2Col.points = new Vector2[] {
                new Vector2(-14f,-9.25f),new Vector2(-17f,-9.25f),new Vector2(-17f,-5.4f),new Vector2(-10.15f,-5.4f),new Vector2(-10.15f,-9.25f),new Vector2(-12.2f,-9.25f)
            };

            //工具室
            EdgeCollider2D ToolCol = Cafe.gameObject.AddComponent<EdgeCollider2D>();
            ToolCol.points = new Vector2[] {
                new Vector2(-14f,-13.68f),new Vector2(-17f,-13.68f),new Vector2(-17f,-17.55f),new Vector2(-9.95f,-17.55f),new Vector2(-9.95f,-13.68f),new Vector2(-12.2f,-13.68f)
            };

            //倉庫
            EdgeCollider2D WareHouseCol = Cafe.gameObject.AddComponent<EdgeCollider2D>();
            WareHouseCol.points = new Vector2[] {
                new Vector2(-19.3f,-12.5f),new Vector2(-19.3f,-17.3f),new Vector2(-26.35f,-17.3f),new Vector2(-26.35f,-4.6f),new Vector2(-23.95f,-4.6f),new Vector2(-23.95f,-3.75f),new Vector2(-26.35f,-3.75f),new Vector2(-26.35f,4f)
            };

            //倉庫
            EdgeCollider2D WorkRoomCol = Cafe.gameObject.AddComponent<EdgeCollider2D>();
            WorkRoomCol.points = new Vector2[] {
                new Vector2(-26.35f,6f),new Vector2(-26.35f,9f),new Vector2(-19.3f,9f),new Vector2(-19.3f,2.6f)
            };
        }
    }
}
