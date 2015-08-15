using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class TankModel : MonoBehaviour {
	public AudioClip normalVoice ;
	public AudioClip runVoice;
	private AudioSource normalSource;
	private AudioSource runSource;

	public GameObject wheelColliderPrefab;
	private WheelCollider wheelCollder;
	public Camera camera_near;
	public Camera camera_far;
	bool flag = false;

	public Transform [] leftWheels;
	public Transform [] rightWheels;
	public Transform [] leftBone;
	public Transform [] rightBone;
	public Transform[] leftUpperWheels;
	public Transform[] rightUpperWheels;
	public GameObject rightTrack;
	public GameObject leftTrack;

	private WheelData [] _leftUpperWheels;
	private WheelData[] _rightUpperWheels;
	private WheelAndBoneData [] _leftWheels;
	private WheelAndBoneData[] _rightWheels;
	private Vector2 trackTextureOffset = Vector2.zero;

	public float motorTorque = 200.0f;
	public float brakeTorque = 200.0f;
	public float steer = 50;
	public float brake = 500.0f;

	// Use this for initialization
	void Start () {
		if (wheelColliderPrefab == null) {
			Debug.Log ("wheel collider prefab is null");
			return;
		}
		if (leftWheels == null) {
			Debug.Log("left wheel is null");
			return;
		}
		if (rightWheels == null) {
			Debug.Log("right wheel is null");
			return ;
		}
		if (leftUpperWheels == null) {
			Debug.Log("leftUpper wheels are null");
		}
		if (rightUpperWheels == null) {
			Debug.Log("rightUpperWheels wheels are null");
		}

		if (leftBone.Length != leftWheels.Length || rightBone.Length != rightWheels.Length) {
			Debug.Log("bone not match with the wheel");
			return ;
		}

		normalSource = SetUpEngineAudioSource (normalVoice);
		runSource = SetUpEngineAudioSource (runVoice);

		wheelCollder = wheelColliderPrefab.GetComponent<WheelCollider>();
		_leftWheels = new WheelAndBoneData[leftWheels.Length];
		_rightWheels = new WheelAndBoneData[rightWheels.Length];

		for (int i = 0; i < leftWheels.Length; i++) {
			_leftWheels[i] = addWheelCollider(leftWheels[i],leftBone[i],wheelCollder);
		}

		for (int i = 0; i < rightWheels.Length; i++) {
			_rightWheels[i] = addWheelCollider(rightWheels[i],rightBone[i],wheelCollder);
		}

	}


	void Update()
	{

		float engine = motorTorque*Input.GetAxis("Vertical");
		float steerG = steer*Input.GetAxis("Horizontal");
		if (engine != 0) {
			normalSource.volume = 0;
			runSource.volume = 0;
		} else {
			normalSource.volume = 0;
			runSource.volume = 0;
		}
		if (Input.GetKeyDown (KeyCode.Tab))
			flag = !flag;
		if (flag) {
			camera_near.depth = 0;
			camera_far.depth = 1;
		} else {
			camera_far.depth = 0 ;
			camera_near.depth = 1 ;
		}

		if (Input.GetKey (KeyCode.A)) {
			UpdateTrack (engine,steerG,_leftWheels,leftTrack,trackTextureOffset,engine<0);
			UpdateTrack (engine/2,0,_rightWheels,rightTrack,trackTextureOffset,engine<0);
		} else if (Input.GetKey (KeyCode.D)) {
			UpdateTrack (engine/2 ,0, _leftWheels, leftTrack, trackTextureOffset, engine < 0);
			UpdateTrack (engine,steerG , _rightWheels, rightTrack, trackTextureOffset, engine < 0);
		} else {
			UpdateTrack (engine,steerG,_leftWheels,leftTrack,trackTextureOffset,engine<0);
			UpdateTrack (engine,steerG,_rightWheels,rightTrack,trackTextureOffset,engine<0);
		}

		if (Input.GetKey (KeyCode.Space)) {
			SetBrake (brake, _leftWheels);
			SetBrake (brake, _rightWheels);
		} else {
			SetBrake (0, _leftWheels);
			SetBrake (0, _rightWheels);
		}

	}

	void OnCollisionEnter(Collision collision)
	{
		Debug.Log ("enter "+collision.transform.name);
	}

	void OnCollisionStay(Collision collision)
	{
		Debug.Log ("stay "+collision.transform.name);
	}
	void OnCollisionExit(Collision collision)
	{
		Debug.Log ("exit "+collision.transform.name);
	}

	WheelAndBoneData addWheelCollider(Transform wheel,Transform bone,WheelCollider wheelCollider)
	{
		WheelAndBoneData wd = new WheelAndBoneData ();
		//个人对wheelcollider悬挂系统不理解，但是官方API上指的是沿着Y轴向下，所以个人有必要认为wheelcollider的
		//y轴应该向上,我这里预设值是Y轴向上的
		GameObject go = new GameObject ("Collider"+wheel.name);
		//set the empty has the same level with the wheel
		go.transform.parent = this.transform;
		go.transform.position = wheel.position;
		WheelCollider col = (WheelCollider) go.AddComponent(typeof(WheelCollider));
		col.mass = wheelCollder.mass;
		col.center = wheelCollder.center;
		col.radius = wheelCollder.radius;
		col.suspensionDistance = wheelCollder.suspensionDistance;
		col.suspensionSpring = wheelCollder.suspensionSpring;
		col.forwardFriction = wheelCollder.forwardFriction;
		col.sidewaysFriction = wheelCollder.sidewaysFriction;

		wd.wheelTransform = wheel;
		wd.wheelStartPos = wheel.localPosition;
		wd.wheelRotationAngles = wheel.localEulerAngles;
		wd.collider = col;
		wd.boneTransform = bone;
		wd.boneStartPos = bone.localPosition;

		return wd;
	}

	private WheelData SetupUpperWheels(Transform wheel){
		WheelData result = new WheelData();
		
		result.wheelTransform = wheel;
		result.wheelStartPos = wheel.transform.localPosition;
		result.wheelRotationAngles = wheel.localEulerAngles;
		
		return result;
		
	}

	private float CalculateSmoothRpm(WheelAndBoneData [] wheels){
		float rpm = 0.0f;
		List<int> grWheel = new List<int>();
		
		for (int i = 0; i<wheels.Length; i++) {
			if(wheels[i].collider.isGrounded)
				grWheel.Add(i);
		}
		
		if (grWheel.Count == 0) {
			foreach (WheelAndBoneData wb in wheels) {
				rpm += wb.collider.rpm;
			}
			rpm /= wheels.Length;
		} else {
			for(int i = 0;i<grWheel.Count;i++){
				rpm += wheels[grWheel[i]].collider.rpm;
			}
			rpm /= grWheel.Count;
		}
		
		return rpm;
	}

	private float RpmToVelocity(float radius,WheelAndBoneData [] wheels)
	{
		float rpm = CalculateSmoothRpm (wheels);
		return rpm * 2 * Mathf.PI * radius / 60.0f;
	}
	

	public void UpdateTrack(float MotorForce,float steer,WheelAndBoneData [] wheels,GameObject track,Vector2 trackTextureOffset,bool isInverse = false){
		float rpm = CalculateSmoothRpm (wheels);
		float velocity = RpmToVelocity (wheels[0].collider.radius,wheels);
		if (isInverse) {
			rpm *= -1;
			velocity *= -1 ;
		}
		
		foreach (WheelAndBoneData wd in wheels) {
			wd.collider.motorTorque = MotorForce;
			wd.collider.steerAngle = steer;
			wd.collider.brakeTorque = 0;
			wd.wheelTransform.Rotate(Time.deltaTime * rpm / 60.0f,0,0);
		}

		//y axis
		trackTextureOffset[1] = Mathf.Repeat(trackTextureOffset[1] + Time.deltaTime*velocity,1.0f);
		if(track.GetComponent<Renderer>().material.GetTexture("_MainTex")){
			track.GetComponent<Renderer>().material.SetTextureOffset("_MainTex",trackTextureOffset);	
		}
		if(track.GetComponent<Renderer>().material.GetTexture("_BumpMap")){
			track.GetComponent<Renderer>().material.SetTextureOffset("_BumpMap",trackTextureOffset);			
		}
	}

	public void SetBrake(float brake,WheelAndBoneData [] wheels)
	{
		foreach (WheelAndBoneData wd in wheels) {
			wd.collider.brakeTorque = brake;
		}
	}

	private AudioSource SetUpEngineAudioSource(AudioClip clip)
	{
		AudioSource source = gameObject.AddComponent<AudioSource>();
		source.clip = clip;
		source.volume = 0;
		source.loop = true;
		
		// start the clip from a random point
		source.time = Random.Range(0f, clip.length);
		source.Play();
		source.minDistance = 5;
		source.maxDistance = 500;
		source.dopplerLevel = 0;
		return source;
	}
}
