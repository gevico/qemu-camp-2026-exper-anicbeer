/*
 * RISC-V translation routines for G233 custom extensions
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#define REQUIRE_G233(ctx) do {               \
    if (!ctx->cfg_ptr->ext_g233) {           \
        return false;                        \
    }                                        \
} while (0)

static bool trans_dma(DisasContext *ctx, arg_r *a)
{
    REQUIRE_G233(ctx);

    TCGv dest = get_gpr(ctx, a->rd, EXT_NONE);
    TCGv src = get_gpr(ctx, a->rs1, EXT_NONE);
    TCGv grain = get_gpr(ctx, a->rs2, EXT_NONE);

    gen_helper_dma_transpose(tcg_env, dest, src, grain);

    return true;
}

static bool trans_gemm(DisasContext *ctx, arg_r *a)
{
    REQUIRE_G233(ctx);

    TCGv c = get_gpr(ctx, a->rd, EXT_NONE);
    TCGv a_addr = get_gpr(ctx, a->rs1, EXT_NONE);
    TCGv b_addr = get_gpr(ctx, a->rs2, EXT_NONE);

    gen_helper_g233_gemm(tcg_env, c, a_addr, b_addr);

    return true;
}

static bool trans_vadd(DisasContext *ctx, arg_r *a)
{
    REQUIRE_G233(ctx);

    TCGv c = get_gpr(ctx, a->rd, EXT_NONE);
    TCGv a_addr = get_gpr(ctx, a->rs1, EXT_NONE);
    TCGv b_addr = get_gpr(ctx, a->rs2, EXT_NONE);

    gen_helper_g233_vadd(tcg_env, c, a_addr, b_addr);

    return true;
}

static bool trans_sort(DisasContext *ctx, arg_r *a)
{
    REQUIRE_G233(ctx);

    TCGv k = get_gpr(ctx, a->rd, EXT_NONE);
    TCGv arr = get_gpr(ctx, a->rs1, EXT_NONE);
    TCGv n = get_gpr(ctx, a->rs2, EXT_NONE);

    gen_helper_g233_sort(tcg_env, k, arr, n);

    return true;
}

static bool trans_crush(DisasContext *ctx, arg_r *a)
{
    REQUIRE_G233(ctx);

    TCGv dst = get_gpr(ctx, a->rd, EXT_NONE);
    TCGv src = get_gpr(ctx, a->rs1, EXT_NONE);
    TCGv n = get_gpr(ctx, a->rs2, EXT_NONE);

    gen_helper_g233_crush(tcg_env, dst, src, n);

    return true;
}

static bool trans_expand(DisasContext *ctx, arg_r *a)
{
    REQUIRE_G233(ctx);

    TCGv dst = get_gpr(ctx, a->rd, EXT_NONE);
    TCGv src = get_gpr(ctx, a->rs1, EXT_NONE);
    TCGv n = get_gpr(ctx, a->rs2, EXT_NONE);

    gen_helper_g233_expand(tcg_env, dst, src, n);

    return true;
}

static bool trans_vdot(DisasContext *ctx, arg_r *a)
{
    REQUIRE_G233(ctx);

    TCGv result = dest_gpr(ctx, a->rd);
    TCGv a_addr = get_gpr(ctx, a->rs1, EXT_NONE);
    TCGv b_addr = get_gpr(ctx, a->rs2, EXT_NONE);

    gen_helper_g233_vdot(result, tcg_env, a_addr, b_addr);
    gen_set_gpr(ctx, a->rd, result);

    return true;
}

static bool trans_vrelu(DisasContext *ctx, arg_r *a)
{
    REQUIRE_G233(ctx);

    TCGv dst = get_gpr(ctx, a->rd, EXT_NONE);
    TCGv src = get_gpr(ctx, a->rs1, EXT_NONE);
    TCGv n = get_gpr(ctx, a->rs2, EXT_NONE);

    gen_helper_g233_vrelu(tcg_env, dst, src, n);

    return true;
}

static bool trans_vscale(DisasContext *ctx, arg_r *a)
{
    REQUIRE_G233(ctx);

    TCGv dst = get_gpr(ctx, a->rd, EXT_NONE);
    TCGv src = get_gpr(ctx, a->rs1, EXT_NONE);
    TCGv scale = get_gpr(ctx, a->rs2, EXT_NONE);

    gen_helper_g233_vscale(tcg_env, dst, src, scale);

    return true;
}

static bool trans_vmax(DisasContext *ctx, arg_r *a)
{
    REQUIRE_G233(ctx);

    TCGv result = dest_gpr(ctx, a->rd);
    TCGv src = get_gpr(ctx, a->rs1, EXT_NONE);
    TCGv n = get_gpr(ctx, a->rs2, EXT_NONE);

    gen_helper_g233_vmax(result, tcg_env, src, n);
    gen_set_gpr(ctx, a->rd, result);

    return true;
}
