#pragma once

#include "../n95a87b_stationaly_position/n95a87b67c_board/square.hpp"
#include "piece_type.hpp"

/// <summary>
///     <pre>
/// 指し手（＾～＾）
/// 
///     - ［ストックフィッシュ］や［大樹の枝］は、［指し手］をビットフィールドとして実装しているが、
///       ［きふわらぷりーＲ］では、ビットフィールドはコード量が多くなって読みにくいんで、クラスとして実装するぜ（＾～＾）
///     </pre>
/// </summary>
class MuzMoveModel
{


    // ========================================
    // フィールド
    // ========================================


    // [移動元]


private:
    /// <summary>
    ///     <pre>
    /// 移動元のマス。
    /// 
    ///     - 旧名： `Move.from()`
    ///     </pre>
    /// </summary>
    Square source_sq_;

    /// <summary>
    ///     <pre>
    /// 移動する前の駒の種類（盤上にある駒の場合）。
    /// 
    ///     - 旧名： `Move.pieceTypeFrom()`
    ///     </pre>
    /// </summary>
    PieceType source_pt_;

    /// <summary>
    ///     <pre>
    /// 移動する前の駒の種類（打つ場合）。
    /// 
    ///     - 旧名： `Move.pieceTypeDropped()`
    ///     </pre>
    /// </summary>
    PieceType source_dropped_pt_;


    // ［移動による変化］


    /// <summary>
    ///     <pre>
    /// 成るか。
    /// 
    ///     - 旧名： `Move.isPromotion()`
    ///     </pre>
    /// </summary>
    bool is_promotion_;

    /// <summary>
    ///     <pre>
    /// 打か。
    /// 
    ///     - 旧名： `Move.isDrop()`
    ///     </pre>
    /// </summary>
    bool is_drop_;

    /// <summary>
    ///     <pre>
    /// 駒を取ったか。
    /// 
    ///     - 旧名： `Move.isCapture()`
    ///     </pre>
    /// </summary>
    bool is_capture_;

    /// <summary>
    ///     <pre>
    /// 駒を取った場合の、取った駒の種類。
    /// 
    ///     - 旧名： `Move.cap()`
    ///     </pre>
    /// </summary>
    PieceType capture_pt_;


    // ［移動先］


    /// <summary>
    ///     <pre>
    /// 移動先のマス。
    /// 
    ///     - 旧名： `Move.to()`
    ///     </pre>
    /// </summary>
    Square destination_sq_;

    /// <summary>
    ///     <pre>
    /// 移動した後の駒の種類。
    /// 
    ///     - 旧名： `Move.pieceTypeTo()`
    ///     </pre>
    /// </summary>
    PieceType destination_pt_;


    // ［組み合わせ］
    //
    //      - 便利なんで、組み合わせを表すクラスを作るかも（＾～＾）


    // TODO: ［移動元］と［移動先］（＾～＾）
    // 
    // TODO: ［移動元］と［移動先］と［成り］（＾～＾）


    // ========================================
    // アクセッサー
    // ========================================


public:


    /// <summary>
    ///     <pre>
    /// 移動元のマス。
    /// 
    ///     - 旧名： `Move.from()`
    ///     </pre>
    /// </summary>
    Square get_source_sq() const { return this->source_sq_; }


    /// <summary>
    ///     <pre>
    /// 移動する前の駒の種類（盤上にある駒の場合）。
    /// 
    ///     - 旧名： `Move.pieceTypeFrom()`
    ///     </pre>
    /// </summary>
    PieceType get_source_pt() const { return this->source_pt_; }


    /// <summary>
    ///     <pre>
    /// 移動する前の駒の種類（打つ場合）。
    /// 
    ///     - 旧名： `Move.pieceTypeDropped()`
    ///     </pre>
    /// </summary>
    PieceType get_source_dropped_pt() const { return this->source_dropped_pt_; }


    // ［移動による変化］


    /// <summary>
    ///     <pre>
    /// 成るか。
    /// 
    ///     - 旧名： `Move.isPromotion()`
    ///     </pre>
    /// </summary>
    bool is_promotion() const { return this->is_promotion_; }


    /// <summary>
    ///     <pre>
    /// 打か。
    /// 
    ///     - 旧名： `Move.isDrop()`
    ///     </pre>
    /// </summary>
    bool is_drop() const { return this->is_drop_; }


    /// <summary>
    ///     <pre>
    /// 駒を取ったか。
    /// 
    ///     - 旧名： `Move.isCapture()`
    ///     </pre>
    /// </summary>
    bool is_capture() const { return this->is_capture_; }


    /// <summary>
    ///     <pre>
    /// 駒を取った場合の、取った駒の種類。
    /// 
    ///     - 旧名： `Move.cap()`
    ///     </pre>
    /// </summary>
    PieceType capture_pt() const { return this->capture_pt_; }


    // ［移動先］


    /// <summary>
    ///     <pre>
    /// 移動先のマス。
    /// 
    ///     - 旧名： `Move.to()`
    ///     </pre>
    /// </summary>
    Square destination_sq() const { return this->destination_sq_; }


    /// <summary>
    ///     <pre>
    /// 移動した後の駒の種類。
    /// 
    ///     - 旧名： `Move.pieceTypeTo()`
    ///     </pre>
    /// </summary>
    PieceType destination_pt() const { return this->destination_pt_; }
};

