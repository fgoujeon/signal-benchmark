#ifndef TESTER_POLICIES_C_STYLE_HPP
#define TESTER_POLICIES_C_STYLE_HPP

#include <list>

struct c_style_tester_policy
{
    struct event_sender
    {
        private:
            using fn_ptr = void(*)(void* /*context*/, int);

            struct fn_ptr_and_context
            {
                fn_ptr_and_context(fn_ptr pf, void* context):
                    pf(pf),
                    context(context)
                {
                }

                fn_ptr pf;
                void* context;
            };

            using fn_ptr_and_context_list = std::list<fn_ptr_and_context>;

        public:
            using connection_id = typename fn_ptr_and_context_list::iterator;

        public:
            connection_id connect(const fn_ptr pf, void* pctx)
            {
                fns_.emplace_back(pf, pctx);
                auto it = fns_.end();
                return --it;
            }

            void disconnect(const connection_id id)
            {
                fns_.erase(id);
            }

            void send(const int i)
            {
                for(const auto& fn: fns_)
                    fn.pf(fn.context, i);
            }

        private:
            fn_ptr_and_context_list fns_;
    };

    struct event_receiver
    {
        public:
            event_receiver(event_sender& sender):
                sender_(sender),
                connection_id_(sender.connect(&on_call, this))
            {
            }

            ~event_receiver()
            {
                sender_.disconnect(connection_id_);
            }

            int get_total() const
            {
                return i_;
            }

        private:
            static void on_call(void* pcontext, const int value)
            {
                auto& self = *reinterpret_cast<event_receiver*>(pcontext);
                self.i_ += value;
            }

        private:
            event_sender& sender_;
            event_sender::connection_id connection_id_;
            int i_ = 0;
    };

    static const char* get_name()
    {
        return "C-style";
    }
};

#endif
