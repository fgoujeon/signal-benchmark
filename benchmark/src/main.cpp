#include "tester_policies/c_style.hpp"
#include "tester_policies/fgsig.hpp"
#include "tester_policies/sigc.hpp"
#include <chrono>
#include <vector>
#include <sstream>
#include <iostream>
#include <cassert>

template<class Policy>
void test(const int receiver_count, const int event_count)
{
    using event_sender = typename Policy::event_sender;
    using event_receiver = typename Policy::event_receiver;

    const auto begin_time = std::chrono::steady_clock::now();

    {
        event_sender sender;

        std::list<event_receiver> receivers;
        for(auto i = 0; i < receiver_count; ++i)
            receivers.emplace_back(sender);

        for(auto i = 0; i < event_count; ++i)
            sender.send(1);

        //check result
        for(const auto& receiver: receivers)
        {
            const auto total = receiver.get_total();
            if(total != event_count)
            {
                std::ostringstream oss;
                oss << Policy::get_name() << " failed: expected " << event_count << ", got " << total << ".";
                throw std::runtime_error(oss.str());
            }
        }
    }

    const auto end_time = std::chrono::steady_clock::now();

    const auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - begin_time).count();

    std::cout << Policy::get_name() << ": " << duration_ms << " ms\n";
}

void test_all(const int receiver_count, const int event_count)
{
    std::cout << receiver_count << " receivers, " << event_count << " events:\n";
    test<c_style_tester_policy>(receiver_count, event_count);
    test<fgsig_tester_policy>(receiver_count, event_count);
    test<sigc_tester_policy>(receiver_count, event_count);
    std::cout << '\n';
}

int main()
{
    test_all(10, 1e8);
    test_all(1e7, 10);
}
