#ifndef MadgwickAHRS_h
#define MadgwickAHRS_h

class MadgwickAHRS {
	//----------------------------------------------------------------------------------------------------
	// Variable declaration
private:
	float sampleFreq = 72.7f;		// sample frequency in Hz
	float betaDef = 0.1f;
	float beta;				// algorithm gain
	float q0, q1, q2, q3;	// quaternion of sensor frame relative to auxiliary frame

	//---------------------------------------------------------------------------------------------------
	// Function declarations
public:
	MadgwickAHRS(){
		beta = betaDef;
		q0 = 1.0f;
		q1 = 0.0f;
		q2 = 0.0f;
		q3 = 0.0f;
	};
	void MadgwickAHRSupdate(float gx, float gy, float gz, float ax, float ay, float az, float mx, float my, float mz);
	void MadgwickAHRSupdateIMU(float gx, float gy, float gz, float ax, float ay, float az);
	float invSqrt(float x);
	float getBeta() {return this->beta;}
	float getQ0() {return this->q0;}
	float getQ1() {return this->q1;}
	float getQ2() {return this->q2;}
	float getQ3() {return this->q3;}
	~MadgwickAHRS(){};
};

#endif
//=====================================================================================================
// End of file
//=====================================================================================================
