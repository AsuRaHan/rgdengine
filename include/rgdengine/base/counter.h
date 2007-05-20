#ifndef COUNTER_H
#define COUNTER_H

namespace base{

class counter
{
	public:
		counter();
		virtual ~counter();

		// �������������
		static bool init();

		// �������������
		static double getCurrentTime();

		// �������������
		void startTiming();

		// �������������
		double getTimeElapsed();

	protected:
		static double frequency;
		double startTime;
};

} // namespace base

#endif // COUNTER_H