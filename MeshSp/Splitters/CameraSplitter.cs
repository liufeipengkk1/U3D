using UnityEngine;
using System.Collections;
using System;

[AddComponentMenu("Mesh Splitting/ Camera Splitter")]
[RequireComponent(typeof(Camera))]
[RequireComponent(typeof(LineRenderer))]

public class CameraSplitter : MonoBehaviour {

	private bool cutMode = false;
	private Camera cam ;
	private Vector3 startPos ;
	private Vector3 endPos ;
	private bool hitMode = false;
	private LineRenderer lineRender ;
	public Material material ;

	public float CutPlaneDistanceFormCam = 1f;
	public float CutPlaneSize = 2f;

	void Awake()
	{
		cam = GetComponent<Camera>(); 
		startPos = Vector3.zero;
		endPos = Vector3.zero;
		cutMode = false;
		lineRender = GetComponent<LineRenderer>();

		lineRender.enabled = false;
		lineRender.material = material;
		lineRender.SetColors(Color.black,Color.black);
		lineRender.SetWidth(0.02f,0.02f);
	}

	void Update () {
		if (Input.GetMouseButtonDown (0)) 
		{
			lineRender.enabled = true;
			startPos = GetMousePos();
			lineRender.SetPosition(0,startPos);

		} else if (Input.GetMouseButtonUp (0)) 
		{
			lineRender.enabled = false;
			endPos = GetMousePos();
			if(startPos != endPos)
			{
				cutMode = true;
				CreatCutPlane();
			}

		}

		lineRender.SetPosition (1,GetMousePos());
	}

	// Mesh Collider 上检测不到点的碰撞,所以把线画到一个平面上
	private Vector3 GetMousePos()
	{
		Ray ray = cam.ScreenPointToRay (Input.mousePosition);
		return ray.origin + ray.direction * CutPlaneDistanceFormCam;
	}

	private void CreatCutPlane()
	{
		Vector3 cutPlanePos =  Vector3.Lerp(startPos,endPos,0.5f);;
		Vector3 cutPlaneRight = (endPos - startPos).normalized;
		Vector3 cutPlaneForward = (cutPlanePos - this.transform.position).normalized;
		Vector3 cutPlaneNormal = Vector3.Cross (cutPlaneForward,cutPlaneRight).normalized;

		GameObject cutPlane = new GameObject ("cutPlane",typeof(BoxCollider),typeof(Rigidbody),typeof(SplitterSingleCut));
		//GameObject cutPlane = new GameObject ("cutPlane",typeof(BoxCollider),typeof(Rigidbody));
		Rigidbody rigidBody = cutPlane.GetComponent<Rigidbody> ();
		rigidBody.useGravity = false;
		rigidBody.isKinematic = true;

		BoxCollider boxCollider = cutPlane.GetComponent<BoxCollider>();
		boxCollider.isTrigger = true;

		Transform cutTransform = cutPlane.transform;
		cutTransform.position = cutPlanePos;
		cutTransform.localScale = new Vector3(CutPlaneSize, 0.001f, CutPlaneSize);
		cutTransform.up = cutPlaneNormal;

		//float angleFwd = Vector3.Angle(cutTransform.up,cutPlaneForward);
		//cutTransform.RotateAround(cutPlanePos, cutPlaneNormal, cutPlaneNormal.y < 0f ? -angleFwd : angleFwd);

	}
}
