// You need to submit this file
#pragma once

#include visitor.h
#include <any>

struct calculator : visitor {
    std::any visit_num(num_node *ctx) override {
        return ctx->number;
    }

    std::any visit_add(add_node *ctx) override {
        auto lhs = visit(ctx->lnode);
        auto rhs = visit(ctx->rnode);
        if (auto lp = std::any_cast<long long>(&lhs)) {
            if (auto rp = std::any_cast<long long>(&rhs)) {
                return std::any{*lp + *rp};
            }
        }
        double ld = value_as_double(lhs);
        double rd = value_as_double(rhs);
        return std::any{ld + rd};
    }

    std::any visit_sub(sub_node *ctx) override {
        auto lhs = visit(ctx->lnode);
        auto rhs = visit(ctx->rnode);
        if (auto lp = std::any_cast<long long>(&lhs)) {
            if (auto rp = std::any_cast<long long>(&rhs)) {
                return std::any{*lp - *rp};
            }
        }
        double ld = value_as_double(lhs);
        double rd = value_as_double(rhs);
        return std::any{ld - rd};
    }

    std::any visit_mul(mul_node *ctx) override {
        auto lhs = visit(ctx->lnode);
        auto rhs = visit(ctx->rnode);
        if (auto lp = std::any_cast<long long>(&lhs)) {
            if (auto rp = std::any_cast<long long>(&rhs)) {
                return std::any{*lp * *rp};
            }
        }
        double ld = value_as_double(lhs);
        double rd = value_as_double(rhs);
        return std::any{ld * rd};
    }

    std::any visit_div(div_node *ctx) override {
        auto lhs = visit(ctx->lnode);
        auto rhs = visit(ctx->rnode);
        if (auto lp = std::any_cast<long long>(&lhs)) {
            if (auto rp = std::any_cast<long long>(&rhs)) {
                return std::any{*lp / *rp};
            }
        }
        double ld = value_as_double(lhs);
        double rd = value_as_double(rhs);
        return std::any{ld / rd};
    }

    ~calculator() override = default;

private:
    static double value_as_double(const std::any &v) {
        if (auto p = std::any_cast<double>(&v)) return *p;
        if (auto p2 = std::any_cast<long long>(&v)) return static_cast<double>(*p2);
        // Fallback: treat empty/unknown as 0.0
        return 0.0;
    }
};

