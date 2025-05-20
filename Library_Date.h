#pragma once 

#include <iostream>
#include <string>
#include <vector>
#include "C:\Users\Al-MBTKR\years1 LnC++\All My Libraries\Library_String.h"

using namespace std;

class clssDate
{
private:
	string _Date;
	struct strDate
	{
		short DAY = 0;
		short MONTH = 0;
		short YEAR = 0;
		short DayOrder = 0;
	} _strDate;

public:
	clssDate(string Date)
	{
		this->_Date = Date;

		vector<string> Data_valus = clssString::SplitString(_Date, "/");

		_strDate.DAY = stoi(Data_valus.at(0));
		_strDate.MONTH = stoi(Data_valus.at(1));
		_strDate.YEAR = stoi(Data_valus.at(2));
		// check is Date a Valid or not
	}
	clssDate(short Day, short Month, short Year)
	{
		_strDate.DAY = Day;
		_strDate.MONTH = Month;
		_strDate.YEAR = Year;
	}

	// Leap Year
	static bool LeapYear(short Year)
	{
		return (Year % 400 == 0 && !(Year % 100 == 0) || Year % 4 == 0);
	}
	bool LeapYear()
	{
		return LeapYear(_strDate.YEAR);
	}

	// Week Order
	static short Day_WeekOrder(short Day, short Month, short Year)
	{
		// short _A_, _Y_, _M_, _D_ = 0;
		// _A_ = (14 - Month) / 12;
		// _M_ = Month + (12 * _A_) - 2;
		// _Y_ = Year - _A_;
		// _D_ = (Day + _Y_ + (_Y_ / 4) - (_Y_ / 100) + (_D_ / 400) + ((31 * _M_) / 12)) % 7;
		// return _D_;

		tm timeStruct = {};
		timeStruct.tm_year = Year - 1900;
		timeStruct.tm_mon = Month - 1;
		timeStruct.tm_mday = Day;

		mktime(&timeStruct);

		int order = timeStruct.tm_wday;

		return order;
	}
	short Day_WeekOrder()
	{
		return Day_WeekOrder(_strDate.DAY, _strDate.MONTH, _strDate.YEAR);
	}

	// Get Date Today
	strDate DateToday()
	{
		strDate Date;
		time_t now = time(0);
		tm LocalTime;

		localtime_s(&LocalTime, &now);

		Date.YEAR = LocalTime.tm_year + 1900;
		Date.MONTH = LocalTime.tm_mon + 1;
		Date.DAY = LocalTime.tm_mday;
		Date.DayOrder = LocalTime.tm_wday;

		return Date;
	}

	static short DaysInYear(short Year)
	{
		return LeapYear(Year) ? 366 : 365;
	}
	short DaysInYear()
	{
		return DaysInYear(_strDate.YEAR);
	}

	static int HoursInYear(short Year)
	{
		return DaysInYear(Year) * 24;
	}
	int HoursInYear()
	{
		return HoursInYear(_strDate.YEAR);
	}

	static int MinutesInYear(short Year)
	{
		return HoursInYear(Year) * 60;
	}
	int MinutesInYear()
	{
		return MinutesInYear(_strDate.YEAR);
	}

	static long SecondsInYear(short Year)
	{
		return MinutesInYear(Year) * 60;
	}
	long SecondsInYear()
	{
		return SecondsInYear(_strDate.YEAR);
	}

	static short DaysInMonth(short Month, short Year)
	{
		if (Month < 1 || Month > 12) // check Month Valu
		{
			cout << "The \"Monthe\" is NOT Valid" << endl;
			return 0;
		}
		short NumberMonths[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
		return (Month == 2) ? (LeapYear(Year) ? 29 : 28) : NumberMonths[Month - 1];
	}
	short DaysInMonth()
	{
		return DaysInMonth(_strDate.MONTH, _strDate.YEAR);
	}

	static string ShortDayName(short DayWeekOrder)
	{
		string name_day[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
		return name_day[DayWeekOrder];
	}
	string ShortDayName()
	{
		return ShortDayName(Day_WeekOrder());
	}

	static string ShortNameMonths(short Month)
	{
		string ArrayMonths[] = {"January", "February", "March", "April", "May", "Jun", "July", "August", "September", "October", "November", "December"};
		return ArrayMonths[Month - 1];
	}
	string ShortNameMonths()
	{
		return ShortNameMonths(_strDate.MONTH);
	}

	static short Days_Since_YearStart(short Day, short Month, short Year)
	{
		short days = 0;
		for (short i = 1; i <= Month - 1; i++)
			days += DaysInMonth(i, Year);

		days += Day; // Add The Rest of Days
		return days;
	}
	short Days_Since_YearStart()
	{
		return Days_Since_YearStart(_strDate.DAY, _strDate.MONTH, _strDate.YEAR);
	}

	strDate GetBirthDay(strDate Date_Today, strDate Date_Birth)
	{
		strDate BirthDay;

		BirthDay.YEAR = Date_Today.YEAR - Date_Birth.YEAR;
		BirthDay.MONTH = Date_Today.MONTH - Date_Birth.MONTH;
		BirthDay.DAY = Date_Today.DAY - Date_Birth.DAY;

		if (BirthDay.DAY < 0)
		{
			BirthDay.MONTH = BirthDay.MONTH - 1;
			BirthDay.DAY = BirthDay.DAY + DaysInMonth(Date_Today.MONTH - 1, Date_Today.YEAR);
		}
		if (BirthDay.MONTH < 0)
		{
			BirthDay.YEAR = BirthDay.YEAR - 1;
			BirthDay.MONTH = BirthDay.MONTH + 12;
		}
		return BirthDay; // Birthday by Years and Months and Days
	}

	static bool IsEndWeek(short DayOrder)
	{
		return (DayOrder == 6); // 6 == Saturday
	}
	bool IsEndWeek()
	{
		return IsEndWeek(Day_WeekOrder(_strDate.DAY, _strDate.MONTH, _strDate.YEAR));
	}

	static bool IsWeekEnd(short DayOrder)
	{
		return (DayOrder == 4 || DayOrder == 5); // 4 = Thursday  5 = Friday
	}
	bool IsWeekEnd()
	{
		return IsWeekEnd(Day_WeekOrder(_strDate.DAY, _strDate.MONTH, _strDate.YEAR));
	}

	static bool IsDayBusiness(short DayOrder)
	{
		return (!IsWeekEnd(DayOrder));
	}
	bool IsDayBusiness()
	{
		return IsDayBusiness(Day_WeekOrder(_strDate.DAY, _strDate.MONTH, _strDate.YEAR));
	}

	static short Days_Until_End_Week(short DayOrder)
	{
		return (7 - DayOrder);
	}
	short Days_Until_End_Week()
	{
		return Days_Until_End_Week(Day_WeekOrder(_strDate.DAY, _strDate.MONTH, _strDate.YEAR));
	}

	static short Days_Until_End_Month(short Day, short Month, short Year)
	{
		short DaysMonth = DaysInMonth(Month, Year);
		return (DaysMonth - Day);
	}
	short Days_Until_End_Month()
	{
		return Days_Until_End_Month(_strDate.DAY, _strDate.MONTH, _strDate.YEAR);
	}

	static short Days_Until_End_Year(short Day, short Month, short Year)
	{
		short dateCurrent = Days_Since_YearStart(Day, Month, Year);
		return (LeapYear(Year)) ? (366 - dateCurrent) : (365 - dateCurrent);
	}
	short Days_Until_End_Year()
	{
		return Days_Until_End_Year(_strDate.DAY, _strDate.MONTH, _strDate.YEAR);
	}

	// Calender
	static void CalendarMonth(short Day, short Month, short Year)
	{
		cout << endl << "   <---------- " << ShortNameMonths(Month) << " ---------->\n"<< endl;

		cout << "  " << "Sun" << "  " << "Mon" << "  " << "Tue" << "  " << "Wed" << "  " << "Thu" << "  "
			 << "Fri" << "  " << "Sat\n"<< endl;

		short cont;
		for (cont = 0; cont < Day_WeekOrder(1, Month, Year); cont++)
			printf("     ");

		for (short j = 1; j <= (DaysInMonth(Month, Year)); j++)
		{
			printf("%5d", j);
			if (++cont == 7)
			{
				printf("\n");
				cont = 0;
			}
		}
	}
	void CalendarMonth()
	{
		CalendarMonth(_strDate.DAY, _strDate.MONTH, _strDate.YEAR);
	}

	static void CalendarMonthsYear(short Year)
	{
		for (short Month = 1; Month <= 12; Month++)
		{
			CalendarMonth(1,Month, Year);
		}
	}

	void Print()
	{
		cout << "Date : " << _strDate.DAY << "/" << _strDate.MONTH << "/" << _strDate.YEAR << endl;
	}
};
