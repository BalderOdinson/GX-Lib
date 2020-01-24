//
// Created by Oshikuru on 12.9.2019..
//

#ifndef GX_PERMUTATION_ITERATOR_H
#define GX_PERMUTATION_ITERATOR_H

#include <iterator>

template<typename Iterator, typename Indices>
struct permutation_iterator
{
    using iterator_category = std::random_access_iterator_tag;

    explicit permutation_iterator(Iterator iterator, Indices indices) noexcept;
    permutation_iterator(permutation_iterator const& other) noexcept;
    permutation_iterator(permutation_iterator&& other) noexcept;
    ~permutation_iterator() = default;

    permutation_iterator& operator=(permutation_iterator const& other) noexcept;
    permutation_iterator& operator=(permutation_iterator&& other) noexcept;

    permutation_iterator& operator++() noexcept { ++indices_; return *this; }
    permutation_iterator operator++(int) noexcept {  auto copy = *this; ++*this; return copy; }
    permutation_iterator& operator--() noexcept { --indices_; return *this; }
    permutation_iterator operator--(int) noexcept { auto copy = *this; --* this; return copy; }
    permutation_iterator& operator+=(size_t n) noexcept { indices_ += n; return *this; }
    permutation_iterator& operator-=(size_t n) noexcept { indices_ -= n; return *this; }

    friend permutation_iterator& operator+(permutation_iterator& iter, size_t n) noexcept { return iter += n; }
    friend permutation_iterator& operator-(permutation_iterator& iter, size_t n) noexcept { return iter -= n; }
    friend permutation_iterator& operator+(size_t n, permutation_iterator& iter) noexcept { return iter += n; }
    friend permutation_iterator& operator-(permutation_iterator& lhs, permutation_iterator& rhs) noexcept { return lhs.indices_ - rhs.indices_; }

    auto& operator*() { return iterator_[*indices_]; }
    const auto& operator*() const { return iterator_[*indices_]; }
    auto& operator[](size_t index) { return iterator_[indices_[index]]; }
    const auto& operator[](size_t index) const { return iterator_[indices_[index]]; }
    auto &operator->() const { return iterator_[*indices_]; }

    Indices const& index_iterator() const noexcept { return indices_; }

    friend bool operator==(permutation_iterator const& lhs, permutation_iterator const& rhs) { return lhs.indices_ == rhs.indices_; }
    friend bool operator!=(permutation_iterator const& lhs, permutation_iterator const& rhs) { return !operator==(lhs, rhs); }
    friend bool operator< (permutation_iterator const& lhs, permutation_iterator const& rhs) { return lhs.indices_ < rhs.indices_; }
    friend bool operator> (permutation_iterator const& lhs, permutation_iterator const& rhs) { return  operator< (rhs, lhs); }
    friend bool operator<=(permutation_iterator const& lhs, permutation_iterator const& rhs) { return !operator> (lhs, rhs); }
    friend bool operator>=(permutation_iterator const& lhs, permutation_iterator const& rhs) { return !operator< (lhs, rhs); }

private:
    Iterator iterator_;
    Indices indices_;
};

template <typename Iterator, typename Indices>
permutation_iterator<Iterator, Indices>::permutation_iterator(Iterator iterator, Indices indices) noexcept
        : iterator_(iterator), indices_(indices)
{
}

template <typename Iterator, typename Indices>
permutation_iterator<Iterator, Indices>::permutation_iterator(permutation_iterator const& other) noexcept
        : iterator_(other.iterator_), indices_(other.indices_)
{
}

template <typename Iterator, typename Indices>
permutation_iterator<Iterator, Indices>::permutation_iterator(permutation_iterator&& other) noexcept
        : iterator_(std::move(other.iterator_)), indices_(std::move(other.indices_))
{
}

template <typename Iterator, typename Indices>
permutation_iterator<Iterator, Indices>& permutation_iterator<Iterator, Indices>::operator=(
        permutation_iterator const& other) noexcept
{
    iterator_ = other.iterator_;
    indices_ = other.indices_;
    return *this;
}

template <typename Iterator, typename Indices>
permutation_iterator<Iterator, Indices>& permutation_iterator<Iterator, Indices>::operator=(
        permutation_iterator&& other) noexcept
{
    iterator_ = std::move(other.iterator_);
    indices_ = std::move(other.indices_);
    return *this;
}

template <typename Iterator, typename Indices>
permutation_iterator<Iterator, Indices> make_permutation_iterator(Iterator iterator, Indices indices) noexcept
{
    return permutation_iterator<Iterator, Indices>(iterator, indices);
}

#endif //GX_PERMUTATION_ITERATOR_H
