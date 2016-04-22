#include <iostream>
#include <cmath>
#include <queue>
#include <deque>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

int random_no (int a, int b) { return static_cast<int> (1. * rand () * (b - a + 1) / (1. + RAND_MAX) + a); }

class Car_Arrival {
  private :
    double probability;

  public :
    Car_Arrival (double p) : probability (p) {
      srand (static_cast<unsigned> (time (NULL)));
    }

    bool is_arrival () const { return (rand () < probability * RAND_MAX); }
};

class Car {
  private :
    int wtime, in_time, out_time, entrance;

  public :
    Car () {}

    Car (int in, int parking_min, int ent) : wtime (in), in_time (in), out_time (in + parking_min), entrance (ent) {}

    Car (int wt, int in, int parking_min, int ent) : wtime (wt), in_time (in), out_time (in + parking_min), entrance (ent) {}

    int waiting_time () const { return in_time - wtime; }

    int parking_time () const { return out_time - in_time; }

    int drive_out () const { return out_time; }

    int drive_in () const { return in_time; }

    int entno () const { return entrance; }

    friend struct Drive_Out_Earlier;
};

struct Drive_Out_Earlier {
  bool operator() (const Car& a, const Car& b) {
    return a.out_time > b.out_time;
  }
};

template <int FEE>
class Parking_Lot {
  private :
    int max_parking_no;
    int available_parking_no;
    int served_car_no[2];
    int fee_collected;
    int max_waiting_time[2];
    int total_waiting_time[2];
    int total_parking_time[2];
    priority_queue<Car, deque<Car>, Drive_Out_Earlier> driveout_queue;

  public :
    Parking_Lot (int parking_no) : max_parking_no (parking_no), available_parking_no (parking_no), fee_collected(0) {
      for (int i = 0; i < 2; ++ i) {
        served_car_no[i] = 0;
        total_waiting_time[i] = 0;
        max_waiting_time[i] = 0;
        total_parking_time[i] = 0;
      }
    }

    bool space_available () const { return available_parking_no > 0; }

    void car_parking (int wtime, int drive_in, int entrance) {
      if (available_parking_no) {
        int parking_time = random_no (4, 36) * 5;
        int waiting_time = drive_in - wtime;
        driveout_queue.push (Car (wtime, drive_in, parking_time, entrance));
        total_waiting_time[entrance] += waiting_time;
        if (waiting_time > max_waiting_time[entrance]) { max_waiting_time[entrance] = waiting_time; }
        total_parking_time[entrance] += parking_time;
        -- available_parking_no;
      }
    }

    int car_leaving (int drive_out) {
      Car car;
      int n = 0;
      while ( ! driveout_queue.empty () && (driveout_queue.top ().drive_out () == drive_out)) {
        car = driveout_queue.top ();
        fee_collected += FEE * static_cast<int> (ceil (car.parking_time () / 60.));
        ++ served_car_no[car.entno ()];
        driveout_queue.pop ();
        ++ available_parking_no;
        ++ n;
      }

      return n;
    }

    template<int F>
    friend ostream& operator<< (ostream& out, const Parking_Lot<F>& foo) {
      out << "每小時收費價：" << F << "元\n"
          << "停車場車位數：" << foo.max_parking_no << "位\n\n";

      out << setw (24) << "A" << " 入口" << setw (6) << "B" << " 入口\n\n"
          << "各入口車子進出數量："
          << setw (10) << foo.served_car_no[0] << setw (10) << foo.served_car_no[1] << " 輛\n"
          << "各入口平均等候時間："
          << setw (10) << (60. * foo.total_waiting_time[0]) / foo.served_car_no[0]
          << setw (10) << (60. * foo.total_waiting_time[1]) / foo.served_car_no[1] << " 秒\n"
          << "各入口最長等候時間："
          << setw (10) << foo.max_waiting_time[0] << setw (10) << foo.max_waiting_time[1] << " 分";

      return out;
    }
};

int main () {
  int i, j, w;

  Car_Arrival incoming_car0 (0.2), incoming_car1 (0.35);

  Parking_Lot<30> parking_lot (60);

  queue<int> waiting_cars0, waiting_cars1;

  for (i = 0; i <= 1440; ++ i) {
    parking_lot.car_leaving (i);
    if (incoming_car0.is_arrival ()) { waiting_cars0.push (i); }
    if (incoming_car1.is_arrival ()) { waiting_cars1.push (i); }
    if (parking_lot.space_available () && ! waiting_cars0.empty () && ! waiting_cars1.empty ()) {
      if (waiting_cars0.empty ()) {
        w = waiting_cars1.front ();
        waiting_cars1.pop ();
        parking_lot.car_parking (w, i, 1);
      } else if (waiting_cars1.empty ()) {
        w = waiting_cars0.front ();
        waiting_cars0.pop ();
        parking_lot.car_parking (w, i, 0);
      } else if (waiting_cars1.front () >= waiting_cars0.front ()) {
        w = waiting_cars0.front ();
        waiting_cars0.pop ();
        parking_lot.car_parking (w, i, 0);
      } else {
        w = waiting_cars1.front ();
        waiting_cars1.pop ();
        parking_lot.car_parking (w, i, 1);
      }
    }
  }

  while ( ! waiting_cars0.empty () || ! waiting_cars1.empty ()) {
    parking_lot.car_leaving (i);

    if (parking_lot.space_available ()) {
      if (waiting_cars0.empty ()) {
        w = waiting_cars1.front ();
        waiting_cars1.pop ();
        parking_lot.car_parking (w, i, 1);
      } else if (waiting_cars1.empty ()) {
        w = waiting_cars0.front ();
        waiting_cars0.pop ();
        parking_lot.car_parking (w, i, 0);
      } else if (waiting_cars1.front () >= waiting_cars0.front ()) {
        w = waiting_cars0.front ();
        waiting_cars0.pop ();
        parking_lot.car_parking (w, i, 0);
      } else {
        w = waiting_cars1.front ();
        waiting_cars1.pop ();
        parking_lot.car_parking (w, i, 1);
      }
    }
    ++ i;
  }

  cout << parking_lot << endl;

  return 0;
}
