module;

export module Fibo.Logger;

namespace fibo
{
	export class Logger
	{
	public:
		static Logger& createLogger();
		Logger(Logger const&) = delete;
		Logger& operator=(Logger const&) = delete;

	private:
		Logger();
		void initialze();
	};
}