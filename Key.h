#pragma once

class Key
{
public:
	Key();

	static void Update();

	/// <summary>
	/// �L�[���g���K�[����Ă��邩�ǂ����Ԃ�
	/// </summary>
	/// <param name="key">�L�[�R�[�h([DIK_...])</param>
	/// <returns>����Ă����� : true�@����Ă��Ȃ������� : false</returns>
	static bool IsTrigger(int key);

	/// <summary>
	/// �L�[��������Ă��邩(������)
	/// </summary>
	/// <param name="key">�L�[�R�[�h([DIK_...])</param>
	/// <returns>����Ă����� : true�@����Ă��Ȃ������� : false</returns>
	static bool IsPress(int key);

private:

	// �L�[���͌��ʂ��󂯎�锠
	static char keys[256];
	static char preKeys[256];

};
