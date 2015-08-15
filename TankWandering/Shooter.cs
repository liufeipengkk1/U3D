using UnityEngine;
using System.Collections;

public class Shooter : MonoBehaviour {

	public Texture2D shootPng ;
	Rect shootCenter ;
	bool flag = false;
	// Use this for initialization
	void Start () {
		float centerSize = Screen.height * 0.1f;
		shootCenter = new Rect ((Screen.width-centerSize)*0.5f,(Screen.height-centerSize)*0.5f,centerSize,
		                        centerSize);


	}
	
	// Update is called once per frame
	void Update () {
		if (Input.GetMouseButton (1)) {
			flag = true;
		} else {
			flag = false;
		}
	}

	void OnGUI(){
		if (flag) {
			GUI.DrawTexture(shootCenter,shootPng);
			Debug.Log("Shoot");
		}
	}
}
