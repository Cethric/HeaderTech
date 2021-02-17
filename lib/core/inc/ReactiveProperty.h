//
// Created by Blake Rogan on 17/02/2021.
//

#ifndef HEADERTECH_REACTIVEPROPERTY_H
#define HEADERTECH_REACTIVEPROPERTY_H

#include <type_traits>
#include <functional>
#include <forward_list>

namespace HeaderTech::Core {

    template<
            typename PODType,
            typename = std::enable_if<
                    std::is_trivially_copyable_v<PODType> &&
                    std::is_standard_layout_v<PODType>
            >
    >
    class ReactiveProperty final {
        using ResultType = ReactiveProperty<PODType>;
        using IsArithmetic = std::enable_if<std::is_arithmetic_v<PODType>>;
        using IsIntegral = std::enable_if<std::is_arithmetic_v<PODType> && std::is_integral_v<PODType>>;
        using ChangeListener = std::function<void(PODType, PODType)>;
        using ChangeListeners = std::forward_list<ChangeListener>;

    public:
        explicit inline ReactiveProperty(PODType data) noexcept: m_data(data), m_listeners() {}

        inline void RegisterChangeListener(const ChangeListener &listener) { m_listeners.push_front(listener); };

        template<typename = IsArithmetic>
        inline ResultType &operator+(PODType value) {
            return ReactiveProperty(m_data + value);
        }

        template<typename = IsArithmetic>
        inline ResultType &operator-(PODType value) {
            return ReactiveProperty(m_data - value);
        }

        template<typename = IsArithmetic>
        inline ResultType &operator/(PODType value) {
            return ReactiveProperty(m_data / value);
        }

        template<typename = IsArithmetic>
        inline ResultType &operator*(PODType value) {
            return ReactiveProperty(m_data * value);
        }

        template<typename = IsIntegral>
        inline ResultType &operator%(PODType value) {
            return ReactiveProperty(m_data % value);
        }

        template<typename = IsArithmetic>
        inline ResultType &operator+=(PODType value) {
            auto prev = m_data;
            ProcessChange(prev, m_data += value);
            return *this;
        }

        template<typename = IsArithmetic>
        inline ResultType &operator-=(PODType value) {
            auto prev = m_data;
            ProcessChange(prev, m_data -= value);
            return *this;
        }

        template<typename = IsArithmetic>
        inline ResultType &operator/=(PODType value) {
            auto prev = m_data;
            ProcessChange(prev, m_data /= value);
            return *this;
        }

        template<typename = IsArithmetic>
        inline ResultType &operator*=(PODType value) {
            auto prev = m_data;
            ProcessChange(prev, m_data *= value);
            return *this;
        }

        template<typename = IsIntegral>
        inline ResultType &operator%=(PODType value) {
            auto prev = m_data;
            ProcessChange(prev, m_data %= value);
            return *this;
        }

        template<typename = IsArithmetic>
        inline ResultType &operator++() {
            auto prev = m_data;
            ProcessChange(prev, ++m_data);
            return *this;
        }

        template<typename = IsArithmetic>
        inline ResultType &operator--() {
            auto prev = m_data;
            ProcessChange(prev, --m_data);
            return *this;
        }

        template<typename = IsArithmetic>
        inline const ResultType operator++(int) {
            ResultType value(*this);
            ++(*this);
            return value;
        }

        template<typename = IsArithmetic>
        inline const ResultType operator--(int) {
            ResultType value(*this);
            --(*this);
            return value;
        }

        template<typename Other>
        inline bool operator==(const Other &other) const { return m_data == other; }

        template<typename Other>
        inline bool operator==(const ReactiveProperty<Other> &other) const { return m_data == other.Convert(); }

        inline bool operator==(const PODType &other) const { return m_data == other; }

        inline bool operator==(const ResultType &other) const { return operator==(other.m_data); }

        template<typename Other>
        inline bool operator!=(const Other &other) const { return m_data != other; }

        template<typename Other>
        inline bool operator!=(const ReactiveProperty<Other> &other) const { return m_data != other.Convert(); }

        inline bool operator!=(const PODType &other) const { return m_data != other; }

        inline bool operator!=(const ResultType &other) const { return operator!=(other.m_data); }

        template<typename Other>
        inline bool operator>(const Other &other) const { return m_data > other; }

        template<typename Other>
        inline bool operator>(const ReactiveProperty<Other> &other) const { return m_data > other.Convert(); }

        inline bool operator>(const PODType &other) const { return m_data > other; }

        inline bool operator>(const ResultType &other) const { return operator>(other.m_data); }

        template<typename Other>
        inline bool operator<(const Other &other) const { return m_data < other; }

        template<typename Other>
        inline bool operator<(const ReactiveProperty<Other> &other) const { return m_data < other.Convert(); }

        inline bool operator<(const PODType &other) const { return m_data < other; }

        inline bool operator<(const ResultType &other) const { return operator<(other.m_data); }

        template<typename Other>
        inline bool operator>=(const Other &other) const { return m_data >= other; }

        template<typename Other>
        inline bool operator>=(const ReactiveProperty<Other> &other) const { return m_data >= other.Convert(); }

        inline bool operator>=(const PODType &other) const { return m_data >= other; }

        inline bool operator>=(const ResultType &other) const { return operator>=(other.m_data); }

        template<typename Other>
        inline bool operator<=(const Other &other) const { return m_data <= other; }

        template<typename Other>
        inline bool operator<=(const ReactiveProperty<Other> &other) const { return m_data <= other.Convert(); }

        inline bool operator<=(const PODType &other) const { return m_data <= other; }

        inline bool operator<=(const ResultType &other) const { return operator<=(other.m_data); }

        explicit inline operator PODType() {
            return m_data;
        }

        inline PODType Convert() const noexcept { return m_data; }

    protected:
        inline ReactiveProperty(const ReactiveProperty<PODType> &copy) noexcept: m_data(copy.m_data),
                                                                                 m_listeners(copy.m_listeners) {}

        inline void ProcessChange(PODType from, PODType to) {
            for (const auto &listener : m_listeners) { listener(from, to); }
        }

    private:
        PODType m_data;
        ChangeListeners m_listeners;
    };
}

#endif //HEADERTECH_REACTIVEPROPERTY_H
