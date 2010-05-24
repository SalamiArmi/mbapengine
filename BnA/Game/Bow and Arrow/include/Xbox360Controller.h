#include <XInput.h>

struct Xbox360State
{
public:
	bool					error;
	struct					{ float X, Y; } LeftStick, RightStick;
	float					LeftTrigger, RightTrigger;
	struct					{ bool LeftShoulder, RightShoulder, A, B, X, Y, Back, Start, LeftThumb, RightThumb; } Buttons;
	struct					{ bool Up, Down, Left, Right; } DPad;
	struct					{ bool LeftShoulder, RightShoulder, A, B, X, Y, Back, Start, LeftThumb, RightThumb; } ButtonsSingle;
	struct					{ bool Up, Down, Left, Right; } DPadSingle;
	struct					{ bool LeftShoulder, RightShoulder, A, B, X, Y, Back, Start, LeftThumb, RightThumb; } ButtonsOld;
	struct					{ bool Up, Down, Left, Right; } DPadOld;
};

class XInputManager : public singleton<XInputManager>
{
		friend singleton;
public:
	XInputManager();
	~XInputManager();

	void					Update();           // update pads

	const Xbox360State &	GetState(const int pad) const;  // get a pad's info
	void					SetVibration(int pad, float left, float right) const; // set vibration strength

private:

	XINPUT_STATE			state[4];			// xinput states
	Xbox360State			Pads[4];			// represents each gamepad
	Xbox360State			PadError;			// returned on error
};