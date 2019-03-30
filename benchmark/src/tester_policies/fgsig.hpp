#ifndef TESTER_POLICIES_FGSIG_HPP
#define TESTER_POLICIES_FGSIG_HPP

#include <fgsig.hpp>

struct fgsig_tester_policy
{
    struct event_sender
    {
        public:
            using signal = fgsig::signal<void(int)>;

        public:
            template<class Slot>
            auto connect(Slot&& s)
            {
                return fgsig::connect(signal_, std::forward<Slot>(s));
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
            event_receiver(event_sender& sender):
                connection_(sender.connect(slot_))
            {
            }

            int get_total() const
            {
                return slot_.i;
            }

        private:
            slot slot_;
            event_sender::signal::connection<slot> connection_;
    };

    static const char* get_name()
    {
        return "fgsig 0.2.0";
    }
};

#endif
