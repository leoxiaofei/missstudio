#ifndef TASKDEF_H_MISS_
#define TASKDEF_H_MISS_

#include <wx/string.h>
#include <memory>

namespace Miss
{
	class DateBase
	{
	public:
		virtual ~DateBase(){};
		enum {DATETYPE = 100};
		virtual int GetType() = 0;
	};

	class TimeBase
	{
	public:
		virtual ~TimeBase(){};
		enum {TIMETYPE = 200};
		virtual int GetType() = 0;
	};

	class TaskDef
	{
	public:
		bool     bEnable;
		int      nId;
		wxString strData;
		std::tr1::shared_ptr<DateBase> ptDate;
		std::tr1::shared_ptr<TimeBase> ptTime;
	};


	typedef unsigned short Year;
	typedef unsigned short Month;
	typedef unsigned short Day;
	typedef unsigned short Week;
	typedef unsigned short Hour;
	typedef unsigned short Minute;

	class DateUsual : public DateBase
	{
	public:
		Year         year;
		Month        month;
		Day          day;

		enum {TYPE = DATETYPE + 1};
		virtual int GetType(){return TYPE;}
	};

	class DateDaily : public DateBase
	{
	public:
		Year         yStart;
		Month        mStart;
		Day          dStart;
		unsigned int uEvery;

		enum {TYPE = DATETYPE + 2};
		virtual int GetType(){return TYPE;}
	};

	class DateWeekly : public DateBase
	{
	public:
		enum WeekType{WT_SUN, WT_MON, WT_TUES, WT_WED, WT_THURS, WT_FRI, WT_SAT, WT_TOTAL};
		Week week[WT_TOTAL];

		enum {TYPE = DATETYPE + 3};
		virtual int GetType(){return TYPE;}
	};

	class DateMonthly : public DateBase
	{
	public:
		Day day;

		enum {TYPE = DATETYPE + 4};
		virtual int GetType(){return TYPE;}
	};

	class DateYearly : public DateBase
	{
	public:
		Month        mStart;
		Day          dStart;

		enum {TYPE = DATETYPE + 5};
		virtual int GetType(){return TYPE;}
	};

	class TimeUsual : public TimeBase
	{
	public:
		Hour     hour;
		Minute   minute;

		enum {TYPE = TIMETYPE + 1};
		virtual int GetType(){return TYPE;}
	};


	class TimeLaunch : public TimeBase
	{
	public:
		enum {TYPE = TIMETYPE + 2};
		virtual int GetType(){return TYPE;}
	};

	class TimeShut : public TimeBase
	{
	public:
		enum {TYPE = TIMETYPE + 3};
		virtual int GetType(){return TYPE;}
	};

	class TimeNone : public TimeBase
	{
	public:
		enum {TYPE = TIMETYPE + 4};
		virtual int GetType(){return TYPE;}
	};
}


#endif // TASKDEF_H__
