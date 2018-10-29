#ifndef TESTER_POLICIES_SIGC_HPP
#define TESTER_POLICIES_SIGC_HPP

#include <sigc++/signal.h>

struct sigc_tester_policy
{
    struct event_sender
    {
        public:
            using signal = sigc::signal<void(int)>;

        public:
            template<class Slot>
            auto connect(Slot&& s)
            {
                return signal_.connect(std::forward<Slot>(s));
            }

            void send(const int i)
            {
                signal_.emit(i);
            }

        private:
            signal signal_;
    };

    struct event_receiver
    {
        private:
            struct slot
            {
                void operator()(int value)
                {
                    i += value;
                }

                int i = 0;
            };

        public:
            event_receiver(event_sender& sender)
            {
                sender.connect(std::ref(slot_));
            }

            int get_total() const
            {
                return slot_.i;
            }

        private:
            slot slot_;
    };

    static const char* get_name()
    {
        return "sigc++ 2.99.11";
    }
};

#endif
