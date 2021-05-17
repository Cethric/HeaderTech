//
// Created by Blake Rogan on 6/05/2021.
//

#ifndef HEADERTECH_REACTIVE_HPP
#define HEADERTECH_REACTIVE_HPP

#include <vector>
#include <concepts>
#include <functional>
#include <type_traits>

#include <iostream>

namespace HeaderTech::Event::Reactive {
    namespace details {
        enum ReactiveOperation {
            SimpleAssignment,
            AdditionAssignment,
            SubtractionAssignment,
            MultiplicationAssignment,
            DivisionAssignment,
            ModuloAssignment,
            BitwiseAndAssignment,
            BitwiseOrAssignment,
            BitwiseXORAssignment,
            BitwiseLeftShiftAssignment,
            BitwiseRightShiftAssignment,
            PreIncrement,
            PreDecrement,
            PostIncrement,
            PostDecrement,
            InputStream,
        };

        template<typename Type, std::uint64_t SubscriptionSize = 8>
        class ReactiveBase {
        public:
            using ReactiveBaseType = Type;
            using ReactiveBaseClass = ReactiveBase<Type, SubscriptionSize>;

        public:
            inline explicit ReactiveBase(Type &&value) noexcept:
                    m_value(std::forward<Type>(value)), m_handles{nullptr}, m_handlesIndex(0)
            {}

            inline ReactiveBase(const ReactiveBaseClass &copy) noexcept: // NOLINT(google-explicit-constructor)
                    m_value(copy.m_value), m_handles{nullptr}, m_handlesIndex(0)
            {}

            template<typename Assignment>
            inline ReactiveBase &operator+=(Assignment &&value) noexcept
            {
                Type oldValue = m_value;
                ValueChanged(
                        ReactiveOperation::AdditionAssignment,
                        std::forward<decltype(oldValue)>(oldValue),
                        std::forward<decltype(m_value)>(m_value += value)
                );
                return *this;
            }

            template<typename Assignment>
            inline ReactiveBase &operator-=(Assignment &&value) noexcept
            {
                Type oldValue = m_value;
                ValueChanged(
                        ReactiveOperation::SubtractionAssignment,
                        std::forward<decltype(oldValue)>(oldValue),
                        std::forward<decltype(m_value)>(m_value -= value)
                );
                return *this;
            }

            template<typename Assignment>
            inline ReactiveBase &operator*=(Assignment &&value) noexcept
            {
                Type oldValue = m_value;
                ValueChanged(
                        ReactiveOperation::MultiplicationAssignment,
                        std::forward<decltype(oldValue)>(oldValue),
                        std::forward<decltype(m_value)>(m_value *= value)
                );
                return *this;
            }

            template<typename Assignment>
            inline ReactiveBase &operator/=(Assignment &&value) noexcept
            {
                Type oldValue = m_value;
                ValueChanged(
                        ReactiveOperation::DivisionAssignment,
                        std::forward<decltype(oldValue)>(oldValue),
                        std::forward<decltype(m_value)>(m_value /= value)
                );
                return *this;
            }

            template<typename Assignment>
            inline ReactiveBase &operator%=(Assignment &&value) noexcept
            {
                Type oldValue = m_value;
                ValueChanged(
                        ReactiveOperation::ModuloAssignment,
                        std::forward<decltype(oldValue)>(oldValue),
                        std::forward<decltype(m_value)>(m_value %= value)
                );
                return *this;
            }

            template<typename Assignment>
            inline ReactiveBase &operator&=(Assignment &&value) noexcept
            {
                Type oldValue = m_value;
                ValueChanged(
                        ReactiveOperation::BitwiseAndAssignment,
                        std::forward<decltype(oldValue)>(oldValue),
                        std::forward<decltype(m_value)>(m_value &= value)
                );
                return *this;
            }

            template<typename Assignment>
            inline ReactiveBase &operator|=(Assignment &&value) noexcept
            {
                Type oldValue = m_value;
                ValueChanged(
                        ReactiveOperation::BitwiseOrAssignment,
                        std::forward<decltype(oldValue)>(oldValue),
                        std::forward<decltype(m_value)>(m_value |= value)
                );
                return *this;
            }

            template<typename Assignment>
            inline ReactiveBase &operator^=(Assignment &&value) noexcept
            {
                Type oldValue = m_value;
                ValueChanged(
                        ReactiveOperation::BitwiseXORAssignment,
                        std::forward<decltype(oldValue)>(oldValue),
                        std::forward<decltype(m_value)>(m_value ^= value)
                );
                return *this;
            }

            template<typename Assignment>
            inline ReactiveBase &operator<<=(Assignment &&value) noexcept
            {
                Type oldValue = m_value;
                ValueChanged(
                        ReactiveOperation::BitwiseLeftShiftAssignment,
                        std::forward<decltype(oldValue)>(oldValue),
                        std::forward<decltype(m_value)>(m_value <<= value)
                );
                return *this;
            }

            template<typename Assignment>
            inline ReactiveBase &operator>>=(Assignment &&value) noexcept
            {
                Type oldValue = m_value;
                ValueChanged(
                        ReactiveOperation::BitwiseRightShiftAssignment,
                        std::forward<decltype(oldValue)>(oldValue),
                        std::forward<decltype(m_value)>(m_value >>= value)
                );
                return *this;
            }

            inline ReactiveBase &operator++() noexcept
            {
                Type oldValue = m_value;
                ValueChanged(
                        ReactiveOperation::PreIncrement,
                        std::forward<decltype(oldValue)>(oldValue),
                        std::forward<decltype(m_value)>(++m_value)
                );
                return *this;
            }

            inline ReactiveBase &operator--() noexcept
            {
                Type oldValue = m_value;
                ValueChanged(
                        ReactiveOperation::PreDecrement,
                        std::forward<decltype(oldValue)>(oldValue),
                        std::forward<decltype(m_value)>(--m_value)
                );
                return *this;
            }

            inline const ReactiveBase operator++(int) noexcept // NOLINT(readability-const-return-type)
            {
                Type oldValue = m_value;
                auto value    = *this;
                ValueChanged(
                        ReactiveOperation::PostIncrement,
                        std::forward<decltype(oldValue)>(oldValue),
                        std::forward<decltype(m_value)>(++m_value)
                );
                return value;
            }

            inline const ReactiveBase operator--(int) noexcept // NOLINT(readability-const-return-type)
            {
                Type oldValue = m_value;
                auto value    = *this;
                ValueChanged(
                        ReactiveOperation::PostDecrement,
                        std::forward<decltype(oldValue)>(oldValue),
                        std::forward<decltype(m_value)>(--m_value)
                );
                return value;
            }

            inline operator ReactiveBaseType&() noexcept// NOLINT(google-explicit-constructor)
            { return m_value; }

            template<typename ostream>
            ostream &operator<<(ostream &stream)
            { return stream << m_value; }

            template<typename istream>
            istream &operator>>(istream &stream)
            {
                Type oldValue = m_value;
                Type t;
                stream >> t;
                ValueChanged(
                        ReactiveOperation::InputStream,
                        std::forward<decltype(oldValue)>(oldValue),
                        std::forward<decltype(m_value)>(m_value = t)
                );
                return stream;
            }


        private:
            using Handle = std::function<void(ReactiveOperation, const Type &&, const Type &&)>;
            using HandleVector = Handle[SubscriptionSize];

        public:
            inline void Subscribe(const Handle &handle) noexcept
            {
                if (m_handlesIndex >= SubscriptionSize) { return; }
                m_handles[m_handlesIndex++] = handle;
            }

        protected:
            inline void ValueChanged(ReactiveOperation op, const Type &&oldValue, const Type &&newValue) noexcept
            {
                for (std::uint64_t idx = 0; idx < m_handlesIndex; ++idx) {
                    Handle &handle = m_handles[idx];
                    handle(op, std::forward<decltype(oldValue)>(oldValue), std::forward<decltype(newValue)>(newValue));
                }
            }

        protected:
            ReactiveBaseType m_value;

        private:
            HandleVector m_handles;
            std::uint64_t m_handlesIndex;
        };
    }

    using details::ReactiveOperation;

    template<typename Type, std::uint64_t SubscriptionSize = 8>
    class Reactive final : public details::ReactiveBase<Type, SubscriptionSize> {
        using Base = details::ReactiveBase<Type, SubscriptionSize>;
    public:
        inline explicit Reactive(Type &&value) noexcept: Base(std::forward<Type>(value))
        {}

        inline Reactive(const Reactive &copy) noexcept: Base(copy)
        {}

        template<typename Assignment>
        inline Reactive &operator=(Assignment &&value) noexcept
        {
            Type oldValue = Base::m_value;
            Base::ValueChanged(
                    ReactiveOperation::SimpleAssignment,
                    std::forward<decltype(oldValue)>(oldValue),
                    std::forward<decltype(Base::m_value)>(Base::m_value = value)
            );
            return *this;
        }
    };

    template<typename Type, std::uint64_t SubscriptionSize>
    class Reactive<std::vector<Type>, SubscriptionSize> final : public details::ReactiveBase<
            std::vector<Type>,
            SubscriptionSize
    > {
        using Base = details::ReactiveBase<std::vector<Type>, SubscriptionSize>;
    public:
        inline explicit Reactive(std::vector<Type> &&value) noexcept: details::ReactiveBase<std::vector<Type>, SubscriptionSize>(std::forward<std::vector<Type>>(value))
        {}

        inline Reactive(const Reactive &copy) noexcept: details::ReactiveBase<std::vector<Type>, SubscriptionSize>(copy)
        {}

        template<typename Assignment>
        inline Reactive &operator=(Assignment &&value) noexcept
        {
            Type oldValue = Base::m_value;
            Base::ValueChanged(
                    ReactiveOperation::SimpleAssignment,
                    std::forward<decltype(oldValue)>(oldValue),
                    std::forward<decltype(Base::m_value)>(Base::m_value = value)
            );
            return *this;
        }
    };

    template<std::uint64_t SubscriptionSize>
    class Reactive<std::string, SubscriptionSize> final : public details::ReactiveBase<std::string, SubscriptionSize> {
        using Base = details::ReactiveBase<std::string, SubscriptionSize>;
        using BaseClass = typename Base::ReactiveBaseClass;
        using BaseType = typename Base::ReactiveBaseType;
    public:
        inline explicit Reactive(std::string &&value) noexcept: details::ReactiveBase<std::string, SubscriptionSize>(std::forward<std::string>(value))
        {}

        inline Reactive(const Reactive &copy) noexcept: details::ReactiveBase<std::string, SubscriptionSize>(copy)
        {}

        template<typename Assignment>
        inline Reactive &operator=(Assignment &&value) noexcept
        {
            BaseType oldValue = Base::m_value;
            Base::ValueChanged(
                    ReactiveOperation::SimpleAssignment,
                    std::forward<decltype(oldValue)>(oldValue),
                    std::forward<decltype(Base::m_value)>(Base::m_value = value)
            );
            return *this;
        }

        template<std::uint64_t SubStrSubscriptionSize = SubscriptionSize>
        Reactive<std::string, SubStrSubscriptionSize> substr(typename BaseType::size_type offset, typename BaseType::size_type count = BaseType::npos)
        { return Reactive<std::string, SubStrSubscriptionSize>{BaseClass::m_value.substr(offset, count)}; }
    };

    template<typename ostream, typename Type>
    ostream &operator<<(ostream &stream, Reactive<Type> &reactive)
    { return reactive.operator<<(stream); }

    template<typename istream, typename Type>
    istream &operator>>(istream &stream, Reactive<Type> &reactive)
    { return reactive.template operator>>(stream); }
}

#endif //HEADERTECH_REACTIVE_HPP
