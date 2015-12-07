using UnityEngine;
using System.Collections;
using System.Collections.Generic;

// u3d 的网格，顶点可能有很多重合的点
// 索引相对应，顺时针索引
public class BaseMesh {

    public List<BasePoint> points;
    public List<BaseEdge> edges;
    public List<BaseTriangle> triangles;

    private Mesh _mesh;
    private Transform _transform;

    protected int vertexCount;
    protected Vector3 [] vertices;
    protected Vector3 [] normal;
    protected Vector4 [] tangent;
    protected Color [] color;
    protected Vector2 [] uv;
    protected int[] tris;

    public BaseMesh(MeshFilter meshfilter)
    {
        _mesh = meshfilter.mesh;
        _transform = meshfilter.GetComponent<Transform>();

        points = new List<BasePoint>(_mesh.vertexCount);
        edges = new List<BaseEdge>();
        triangles = new List<BaseTriangle>();

        vertices = _mesh.vertices;
        normal = _mesh.normals;
        tangent = _mesh.tangents;
        color = _mesh.colors;
        uv = _mesh.uv;
        tris = _mesh.triangles;
    }


    public void Init()
    {
        for(int i = 0; i < vertexCount;i++)
        {
            BasePoint point = new BasePoint();
            point.localPos = vertices[i];
            point.worldPos = Local2World(vertices[i]);
            point.normal = normal[i];
            point.tangent = tangent[i];
            point.color = color[i];
            point.uv = uv[i];
            point.index = i;

            points.Add(point);
        }

        // add Edges
        int triLen = tris.Length;
        for (int i = 0; i < triLen; i += 3)
        {
            BaseEdge edge1 = new BaseEdge();
            BaseEdge edge2 = new BaseEdge();
            BaseEdge edge3 = new BaseEdge();

            edge1.index = i;
            edge1.p1 = points[tris[i]];
            edge1.p2 = points[tris[i + 1]];

            edge2.index = i + 1;
            edge2.p1 = points[tris[i+1]];
            edge2.p2 = points[tris[i + 2]];

            edge3.index = i + 2;
            edge3.p1 = points[tris[i + 2]];
            edge3.p2 = points[tris[i]];

            edges.Add(edge1);
            edges.Add(edge2);
            edges.Add(edge3);
        }


        // add triangels
        int index = 0;
        for (int i = 0; i < triLen; i += 3)
        {
            BaseTriangle tri = new BaseTriangle();
            tri.p1 = points[tris[i]];
            tri.p2 = points[tris[i + 1]];
            tri.p3 = points[tris[i + 2]];

            tri.e1 = edges[i];
            tri.e2 = edges[i + 1];
            tri.e3 = edges[i + 2];
            tri.index = index++;

            triangles.Add(tri);

        }
    }

    protected Vector3 Local2World(Vector3  localPos)
    {
        Matrix4x4 l2w = _transform.localToWorldMatrix;
        return l2w.MultiplyPoint3x4(localPos);
    }

    protected Vector3 World2Local(Vector3 worldPos)
    {
        Matrix4x4 w2l = _transform.worldToLocalMatrix;
        return w2l.MultiplyPoint3x4(worldPos);
    }

    // 重写插值
    
}
